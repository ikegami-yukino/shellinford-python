#include "shellinford_fm_index.h"
#include <algorithm>
#include <iostream>

namespace shellinford {
  using namespace std;
  fm_index::fm_index(bool use_wavelet_tree)
   : ddic_(0), head_(0) {
    if (use_wavelet_tree) {
      this->sv_ = new wavelet_tree<uint8_t>();
    } else {
      this->sv_ = new wavelet_matrix<uint8_t>();
    }
  }
  fm_index::~fm_index() {
    if (this->sv_) { delete this->sv_; }
  }
  void fm_index::clear() {
    this->sv_->clear();
    this->doctails_.clear();
    this->posdic_.clear();
    this->idic_.clear();
    this->ddic_   = 0;
    this->head_   = 0;
    this->substr_ = "";
  }
  void fm_index::push_back(const string &doc) {
    if (doc.size() <= 0) {
      throw "shellinford::fm_index::push_back()";
    }
    this->substr_ += doc;
    this->doctails_.set(this->doctails_.size() + doc.size() - 1);
  }
  void fm_index::build(char end_marker, uint64_t ddic, bool is_msg) {
    if (is_msg) { cerr << "building burrows-wheeler transform." << endl; }

    this->doctails_.build();
    this->substr_ += end_marker;
    bwt b;
    b.build(this->substr_.c_str());
    string s;
    b.get(s);
    this->head_ = b.head();
    b.clear();
    this->substr_ = "";
    if (is_msg) { cerr << "done." << endl; }

    if (is_msg) { cerr << "building wavelet tree." << endl; }
    this->sv_->build(s.c_str());
    if (is_msg) { cerr << "done." << endl; }

    if (is_msg) { cerr << "building dictionaries." << endl; }
    for (uint64_t c = 0; c < 256; c++) {
      this->rlt_[c] = this->sv_->rank_less_than(this->sv_->size(), c);
    }
    this->ddic_ = ddic;
    this->posdic_.assign(s.size() / this->ddic_ + 1, 0);
    this->idic_.assign(s.size() / this->ddic_ + 1, 0);
    uint64_t i   = this->head_;
    uint64_t pos = this->size() - 1;
    do {
      if ((i % this->ddic_) == 0) {
        this->posdic_[i / this->ddic_] = pos;
      }
      if ((pos % this->ddic_) == 0) {
        this->idic_[pos / this->ddic_] = i;
      }
      uint8_t c = this->sv_->get(i);
      i = this->rlt_[c] + this->sv_->rank(i, c); //LF
      pos--;
    } while (i != this->head_);
    if (is_msg) { cerr << "done." << endl; }
  }
  uint64_t fm_index::get_rows(const string &key) const {
    uint64_t f, l;
    return this->get_rows(key, f, l);
  }
  uint64_t fm_index::get_rows(const string &key,
                              uint64_t &first, uint64_t &last) const {
    uint64_t i = key.size() - 1;
    first = this->rlt_[uint8_t(key[i])] + 1;
    last  = this->rlt_[uint8_t(key[i]) + 1];
    while (first <= last) {
      if (i == 0) { first--; last--; return (last - first  + 1); }
      i--;
      uint8_t c = uint8_t(key[i]);
      first = this->rlt_[c] + this->sv_->rank(first - 1, c) + 1;
      last  = this->rlt_[c] + this->sv_->rank(last,      c);
    }
    return 0;
  }
  uint64_t fm_index::get_position(uint64_t i) const {
    if (i >= this->size()) {
      throw "shellinford::fm_index::get_position()";
    }
    uint64_t pos = 0;
    while (i != this->head_) {
      if ((i % this->ddic_) == 0) {
        pos += (this->posdic_[i / this->ddic_] + 1);
        break;
      }
      uint8_t c = this->sv_->get(i);
      i = this->rlt_[c] + this->sv_->rank(i, c); //LF
      pos++;
    }
    return pos % this->size();
  }
  const string &fm_index::get_substring(uint64_t pos, uint64_t len) {
    if (pos >= this->size()) {
      throw "shellinford::fm_index::get_substring()";
    }
    uint64_t pos_end  = min(pos + len, this->size());
    uint64_t pos_tmp  = this->size() - 1;
    uint64_t i        = this->head_;
    uint64_t pos_idic = (pos_end + this->ddic_ - 2) / this->ddic_;
    if (pos_idic < this->idic_.size()) {
      pos_tmp = pos_idic * this->ddic_;
      i       = this->idic_[pos_idic];
    }

    this->substr_ = "";
    while (pos_tmp >= pos) {
      uint8_t c = this->sv_->get(i);
      i = this->rlt_[c] + this->sv_->rank(i, c); //LF
      if (pos_tmp < pos_end) {
        this->substr_.insert(this->substr_.begin(), c);
      }
      if (pos_tmp == 0) { break; }
      pos_tmp--;
    }
    return this->substr_;
  }
  uint64_t fm_index::get_document_id(uint64_t pos) const {
    if (pos >= this->size()) {
      throw "shellinford::fm_index::get_document_id()";
    }
    return this->doctails_.rank(pos);
  }
  void fm_index::search(const string &key,
                        map<uint64_t, uint64_t> &dids) const {
    dids.clear();
    uint64_t first, last;
    uint64_t rows = this->get_rows(key, first, last);
    if (rows > 0) {
      for (uint64_t i = first; i <= last; i++) {
        uint64_t pos = this->get_position(i);
        uint64_t did = this->get_document_id(pos);
        dids[did]++;
      }
    }
  }
  const string &fm_index::get_document(uint64_t did) {
    if (did >= this->docsize()) {
      throw "shellinford::fm_index::get_document()";
    }
    uint64_t pos = 0;
    if (did > 0) { pos = this->doctails_.select(did - 1) + 1; }
    uint64_t len = this->doctails_.select(did) - pos + 1;
    return this->get_substring(pos, len);
  }
  void fm_index::write(ofstream &ofs) const {
    ofs.write((char *)&(this->ddic_), sizeof(uint64_t));
    ofs.write((char *)&(this->head_), sizeof(uint64_t));
    ofs.write((char *)&(this->rlt_), sizeof(uint64_t) * 256);
    this->sv_->write(ofs);
    this->doctails_.write(ofs);

    vector<uint64_t>::const_iterator ip = this->posdic_.begin();
    vector<uint64_t>::const_iterator ep = this->posdic_.end();
    while (ip != ep) {
      ofs.write((char *)&(*ip), sizeof(uint64_t));
      ip++;
    }
    vector<uint64_t>::const_iterator ii = this->idic_.begin();
    vector<uint64_t>::const_iterator ei = this->idic_.end();
    while (ii != ei) {
      ofs.write((char *)&(*ii), sizeof(uint64_t));
      ii++;
    }
  }
  void fm_index::write(const char *filename) const {
    ofstream ofs(filename, ios::out | ios::binary | ios::trunc);
    if (!ofs) { throw "shellinford::fm_index::write()"; }
    this->write(ofs);
  }
  void fm_index::read(ifstream &ifs) {
    ifs.read((char *)&(this->ddic_), sizeof(uint64_t));
    if (ifs.eof()) { throw "shellinford::fm_index::read()"; }
    ifs.read((char *)&(this->head_), sizeof(uint64_t));
    if (ifs.eof()) { throw "shellinford::fm_index::read()"; }
    ifs.read((char *)&(this->rlt_), sizeof(uint64_t) * 256);
    if (ifs.eof()) { throw "shellinford::fm_index::read()"; }
    this->sv_->read(ifs);
    this->doctails_.read(ifs);

    uint64_t size = this->sv_->size() / this->ddic_ + 1;
    for (uint64_t i = 0; i < size; i++) {
      uint64_t x = 0;
      ifs.read((char *)&x, sizeof(uint64_t));
      if (ifs.eof()) { throw "shellinford::fm_index::read()"; }
      this->posdic_.push_back(x);
    }
    for (uint64_t i = 0; i < size; i++) {
      uint64_t x = 0;
      ifs.read((char *)&x, sizeof(uint64_t));
      if (ifs.eof()) { throw "shellinford::fm_index::read()"; }
      this->idic_.push_back(x);
    }
  }
  void fm_index::read(const char *filename) {
    ifstream ifs(filename, ios::in | ios::binary);
    if (!ifs) { throw "shellinford::fm_index::read()"; }
    this->read(ifs);
  }

  ////////////////////////////////

  bwt::bwt() : size_(0), head_(0) {
  }
  bwt::~bwt() {
  }
  void bwt::clear() {
    this->str_  = NULL;
    this->size_ = 0;
    this->head_ = 0;
    this->sa_.clear();
  }
  void bwt::build(const char *str) {
    srand(unsigned(time(NULL)));
    this->str_ = str;
    this->sa_.clear();
    this->size_ = 0;
    while (this->str_[this->size_] != '\0') {
      this->sa_.push_back(this->size_);
      this->size_++;
    }
    this->sort(0, this->size() - 1, 0);
    for (uint64_t i = 0; i < this->size(); i++) {
      if (this->sa_[i] == 0) { this->head_ = i; break; }
    }
  }
  char bwt::get(uint64_t i) const {
    if (i >= this->size()) {
      throw "shellinford::bwt::get()";
    }
    return this->str_[(this->sa_[i] + this->size() - 1) % this->size()];
  }
  void bwt::get(string &str) const {
    str = "";
    for (uint64_t i = 0; i < this->size(); i++) {
      str += this->get(i);
    }
  }
  void bwt::sort(int64_t begin, int64_t end, uint64_t depth) {
    int64_t a = begin;
    int64_t b = begin;
    int64_t c = end;
    int64_t d = end;
    int64_t size = end - begin + 1;
    if (size <= 1) { return; }

    int64_t pivot_pos = int64_t((double(rand()) / RAND_MAX) * size);
    uint8_t pivot     = this->sa2char(begin + pivot_pos, depth);

    while (1) {
      uint8_t b_ch = this->sa2char(b, depth);
      while ((b <= c) && (b_ch <= pivot)) {
        if (b_ch == pivot) { swap(this->sa_[a], this->sa_[b]); a++; }
        b++;
        if (b >= int64_t(this->size())) { break; }
        b_ch = this->sa2char(b, depth);
      }

      uint8_t c_ch = this->sa2char(c, depth);
      while ((b <= c) && (c_ch >= pivot)) {
        if (c_ch == pivot) { swap(this->sa_[c], this->sa_[d]); d--; }
        c--;
        if (c < 0) { break; }
        c_ch = this->sa2char(c, depth);
      }
      if (b > c) { break; }
      swap(this->sa_[b], this->sa_[c]); b++; c--;
    }

    int64_t eq_size = 0;
    eq_size = (((a - begin) < (b - a)) ? (a - begin) : (b - a));
    for (int64_t i = 0; i < eq_size; i++) {
      swap(this->sa_[begin + i], this->sa_[b - eq_size + i]);
    }
    eq_size = (((d - c) < (end - d)) ? (d - c) : (end - d));
    for (int64_t i = 0; i < eq_size; i++) {
      swap(this->sa_[b + i], this->sa_[end - eq_size + i + 1]);
    }

    this->sort(begin,             begin + b - a - 1, depth    );
    this->sort(begin + b - a,     end   - d + c,     depth + 1);
    this->sort(end   - d + c + 1, end,               depth    );
  }
  uint8_t bwt::sa2char(uint64_t i, uint64_t depth) const {
    uint64_t offset = (this->sa_[i] + depth) % this->size();
    return uint8_t(this->str_[offset]);
  }
}

