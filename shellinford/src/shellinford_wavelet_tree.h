#ifndef SHELLINFORD_WAVELET_TREE
#define SHELLINFORD_WAVELET_TREE

#include "shellinford_succinct_vector.h"
#include "shellinford_bit_vector.h"
#include <cstring>
#include <cmath>
#include <string>
#include <queue>

namespace shellinford {
  // wavelet_tree<T> is template class.
  // T must be uint8_t, uint16_t, uint32_t or uint64_t.
  template<class T>
  class wavelet_tree : public succinct_vector<T> {
    std::vector<bit_vector> bv_;
    std::vector<uint64_t>   rposdic_;
    std::vector<uint64_t>   rlendic_;
    uint64_t bitsize_;
    uint64_t size_;
    uint64_t rdic_depth_;
    uint64_t get(uint64_t i, T c, bool is_rank, bool is_rlt) const;

  public:
    wavelet_tree();
    ~wavelet_tree();
    void clear();
    void build(const char *s);
    void build(std::vector<T> &v);
    uint64_t bitsize() const { return this->bitsize_; }
    uint64_t size() const { return this->size_; }
    uint64_t size(T c) const {
      return this->rank(this->size(), c);
    }
    T get(uint64_t i) const;
    uint64_t rank(uint64_t i, T c) const;
    uint64_t select(uint64_t i, T c) const;
    uint64_t rank_less_than(uint64_t i, T c) const;
    void write(std::ofstream &ofs) const;
    void write(const char *filename) const;
    void read(std::ifstream &ifs);
    void read(const char *filename);
  };

  template<class T>
  struct range {
    uint64_t       pos;
    uint64_t       len;
    uint64_t       depth;
    std::vector<T> vec;
    range(uint64_t p, uint64_t l, uint64_t d,
          const std::vector<T> &v)
     : pos(p), len(l), depth(d), vec(v) {} 
  };

  template<class T>
  wavelet_tree<T>::wavelet_tree()
   : bitsize_(sizeof(T) * 8), size_(0), rdic_depth_(8) {
  }
  template<class T>
  wavelet_tree<T>::~wavelet_tree() {
  }
  template<class T>
  void wavelet_tree<T>::clear() {
    this->bv_.clear();
    this->size_ = 0;
  }
  template<class T>
  void wavelet_tree<T>::build(const char *s) {
    std::vector<T> v;
    while (*s != '\0') { v.push_back(*s); s++; }
    this->build(v);
  }
  template<class T>
  void wavelet_tree<T>::build(std::vector<T> &v) {
    this->bv_.clear();
    this->bv_.assign(this->bitsize(), bit_vector());

    this->size_ = v.size();
    std::queue<range<T> > rq;
    rq.push(range<T>(0, this->size(), 0, v));
    this->rposdic_.push_back(0);
    this->rlendic_.push_back(0);
    while (!(rq.empty())) {
      range<T> r = rq.front();
      rq.pop();
      if (r.depth >= this->rdic_depth_ && r.len == 0) { continue; }
      bit_vector &bv = this->bv_[r.depth];
      std::vector<T> v1;
      std::vector<T> v0;
      for (uint64_t i = 0; i < r.len; i++) {
         uint64_t pos = r.pos + i;
         bool     bit = uint2bit(r.vec[i], r.depth);
         bv.set(pos, bit);
         if (bit) { v1.push_back(r.vec[i]); }
         else     { v0.push_back(r.vec[i]); }
      }
      bv.build();
      if (r.depth < this->rdic_depth_) {
        this->rposdic_.push_back(bv.rank(r.pos, false));
        this->rlendic_.push_back(bv.rank(r.pos + r.len, false)
                                 - this->rposdic_.back());
        this->rposdic_.push_back(bv.rank(r.pos, true));
        this->rlendic_.push_back(bv.rank(r.pos + r.len, true)
                                 - this->rposdic_.back());
      }
      if (r.depth < (this->bitsize() - 1)) {
        uint64_t pos = r.pos;
        uint64_t len = bv.rank(r.pos + r.len, false)
                       - bv.rank(r.pos, false);
        rq.push(range<T>(pos, len, r.depth + 1, v0));
        pos += len;
        len = r.len - len;
        rq.push(range<T>(pos, len, r.depth + 1, v1));
      }
    }
  }
  template<class T>
  T wavelet_tree<T>::get(uint64_t i) const {
    if (i >= this->size()) {
      throw "shellinford::wavelet_tree::get()";
    }
    return this->get(i, 0, false, false);
  }
  template<class T>
  uint64_t wavelet_tree<T>::rank(uint64_t i, T c) const {
    if (i > this->size()) {
      throw "shellinford::wavelet_tree::rank()";
    }
    if (i == 0) { return 0; }
    return this->get(i, c, true, false);
  }
  template<class T>
  uint64_t wavelet_tree<T>::rank_less_than(uint64_t i, T c) const {
    if (i > this->size()) {
      throw "shellinford::wavelet_tree::rank_less_than()";
    }
    if (i == 0) { return 0; }
    return this->get(i, c, true, true);
  }
  template<class T>
  uint64_t wavelet_tree<T>::select(uint64_t i, T c) const {
    if (i >= this->size(c)) {
      throw "shellinford::wavelet_tree::select()";
    }

    uint64_t left  = 0;
    uint64_t right = this->size();
    while (left < right) {
      uint64_t pivot = (left + right) / 2;
      uint64_t value = this->rank(pivot, c);
      if      (i < value) { right = pivot; }
      else if (i > value) { left  = pivot + 1; }
      else {
        while ((pivot > 0) && (this->get(pivot) != c)) {
          pivot++;
        } 
        return pivot;
      }
    }
    throw "shellinford::wavelet_tree::select()";
  }
  template<class T>
  void wavelet_tree<T>::write(std::ofstream &ofs) const {
    ofs.write((char *)&(this->size_), sizeof(uint64_t));

    for (uint64_t i = 0; i < this->bitsize(); i++) {
      this->bv_[i].write(ofs);
    }
    uint64_t rdic_size = pow(2, (this->rdic_depth_ + 2)) - 1;
    for (uint64_t i = 0; i < rdic_size; i++) {
      ofs.write((char *)&(this->rposdic_[i]), sizeof(uint64_t));
      ofs.write((char *)&(this->rlendic_[i]), sizeof(uint64_t));
    }
  }
  template<class T>
  void wavelet_tree<T>::write(const char *filename) const {
    std::ofstream ofs(filename,
                  std::ios::out | std::ios::binary | std::ios::trunc);
    if (!ofs) { throw "shellinford::wavelet_tree::write()"; }
    this->write(ofs);
  } 
  template<class T>
  void wavelet_tree<T>::read(std::ifstream &ifs) {
    ifs.read((char *)&(this->size_), sizeof(uint64_t));
    if (ifs.eof()) { throw "shellinford::wavelet_tree::read()"; }

    for (uint64_t i = 0; i < this->bitsize(); i++) {
      this->bv_.push_back(bit_vector());
      this->bv_.back().read(ifs);
    }
    uint64_t rdic_size = pow(2, (this->rdic_depth_ + 2)) - 1;
    for (uint64_t i = 0; i < rdic_size; i++) {
      uint64_t x = 0;
      ifs.read((char *)&x, sizeof(uint64_t));
      if (ifs.eof()) { throw "shellinford::wavelet_tree::read()"; }
      this->rposdic_.push_back(x);
      ifs.read((char *)&x, sizeof(uint64_t));
      if (ifs.eof()) { throw "shellinford::wavelet_tree::read()"; }
      this->rlendic_.push_back(x);
    }
  }
  template<class T>
  void wavelet_tree<T>::read(const char *filename) {
    std::ifstream ifs(filename, std::ios::in | std::ios::binary);
    if (!ifs) { throw "shellinford::wavelet_tree::read()"; }
    this->read(ifs);
  }

  //////// private member functions ////////
  template<class T>
  uint64_t wavelet_tree<T>::get(uint64_t i, T c,
                                bool is_rank, bool is_rlt) const {
    T value = 0;
    uint64_t rlt = 0;
    uint64_t dic_index = 0;
    range<T> r(0, this->size(), 0, std::vector<T>());
    while (r.depth < this->bitsize()) {
      const bit_vector &bv = this->bv_[r.depth];
      bool b = false;
      if (is_rank) {
        b = uint2bit(c, r.depth);
      } else {
        b = bv.get(r.pos + i);
        value <<= 1;
        if (b) { value |= 0x1ULL; }
      }

      uint64_t rank_pos = 0;
      uint64_t rank_len = 0;
      if (r.depth < this->rdic_depth_) {
        dic_index = dic_index * 2 + 1;
        if (b) { dic_index++; }
        rank_pos = this->rposdic_[dic_index];
        rank_len = this->rlendic_[dic_index];
      } else {
        rank_pos = bv.rank(r.pos, b);
        rank_len = bv.rank(r.pos + r.len, b) - rank_pos;
      }
      uint64_t j = bv.rank(r.pos + i, b) - rank_pos;
      if (is_rlt && b) { rlt += (i - j); }
      i = j;

      uint64_t pos = r.pos;
      uint64_t len = rank_len;
      if (b) { pos += (r.len - len); }

      r = range<T>(pos, len, r.depth + 1, r.vec);
    }
    if (is_rlt)   { i = rlt; }
    if (!is_rank) { i = uint64_t(value); }
    return i;
  }
}

#endif

