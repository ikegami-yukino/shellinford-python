#include "shellinford_bit_vector.h"

namespace shellinford {
  using namespace std;
  inline uint64_t rank64(uint64_t x, uint64_t i, bool b) {
    if (!b) { x = ~x; }
    x <<= (SMALL_BLOCK_SIZE - i);
    x = ((x & 0xaaaaaaaaaaaaaaaaULL) >>  1)
      +  (x & 0x5555555555555555ULL);
    x = ((x & 0xccccccccccccccccULL) >>  2)
      +  (x & 0x3333333333333333ULL);
    x = ((x & 0xf0f0f0f0f0f0f0f0ULL) >>  4)
      +  (x & 0x0f0f0f0f0f0f0f0fULL);
    x = ((x & 0xff00ff00ff00ff00ULL) >>  8)
      +  (x & 0x00ff00ff00ff00ffULL);
    x = ((x & 0xffff0000ffff0000ULL) >> 16)
      +  (x & 0x0000ffff0000ffffULL);
    x = ((x & 0xffffffff00000000ULL) >> 32)
      +  (x & 0x00000000ffffffffULL);
    return x;
  }
  inline uint64_t select64(uint64_t x, uint64_t i, bool b) {
    if (!b) { x = ~x; }
    uint64_t x1 = ((x  & 0xaaaaaaaaaaaaaaaaULL) >>  1)
                +  (x  & 0x5555555555555555ULL);
    uint64_t x2 = ((x1 & 0xccccccccccccccccULL) >>  2)
                +  (x1 & 0x3333333333333333ULL);
    uint64_t x3 = ((x2 & 0xf0f0f0f0f0f0f0f0ULL) >>  4)
                +  (x2 & 0x0f0f0f0f0f0f0f0fULL);
    uint64_t x4 = ((x3 & 0xff00ff00ff00ff00ULL) >>  8)
                +  (x3 & 0x00ff00ff00ff00ffULL);
    uint64_t x5 = ((x4 & 0xffff0000ffff0000ULL) >> 16)
                +  (x4 & 0x0000ffff0000ffffULL);

    i++;
    uint64_t pos = 0;
    uint64_t v5 = x5 & 0xffffffffULL;
    if (i > v5) { i -= v5; pos += 32; }
    uint64_t v4 = (x4 >> pos) & 0x0000ffffULL;
    if (i > v4) { i -= v4; pos += 16; }
    uint64_t v3 = (x3 >> pos) & 0x000000ffULL;
    if (i > v3) { i -= v3; pos +=  8; }
    uint64_t v2 = (x2 >> pos) & 0x0000000fULL;
    if (i > v2) { i -= v2; pos +=  4; }
    uint64_t v1 = (x1 >> pos) & 0x00000003ULL;
    if (i > v1) { i -= v1; pos +=  2; }
    uint64_t v0 = (x  >> pos) & 0x00000001ULL;
    if (i > v0) { i -= v0; pos +=  1; }
    return pos;
  }

  bit_vector::bit_vector()
   : size_(0), size1_(0) {
  }
  bit_vector::~bit_vector() {
  }
  void bit_vector::clear() {
    this->v_.clear();
    this->r_.clear();
    this->size_  = 0;
    this->size1_ = 0;
  }
  bool bit_vector::get(uint64_t i) const {
    if (i >= this->size()) { throw "shellinford::bit_vector::get()"; }
    uint64_t q = i / SMALL_BLOCK_SIZE;
    uint64_t r = i % SMALL_BLOCK_SIZE;
    uint64_t m = 0x1ULL << r;
    return this->v_[q] & m;
  }
  void bit_vector::set(uint64_t i, bool b) {
    if (i >= this->size()) { this->size_ = i + 1; }
    uint64_t q = i / SMALL_BLOCK_SIZE;
    uint64_t r = i % SMALL_BLOCK_SIZE;
    while (q >= this->v_.size()) { this->v_.push_back(0); }
    uint64_t m = 0x1ULL << r;
    if (b) { this->v_[q] |=  m; }
    else   { this->v_[q] &= ~m; }
  }
  void bit_vector::build() {
    this->r_.clear();
    this->size1_ = 0;
    for (uint64_t i = 0; i < this->v_.size(); i++) {
      if (i % BLOCK_RATE == 0) {
        this->r_.push_back(this->size(true));
      }
      this->size1_ += rank64(this->v_[i], SMALL_BLOCK_SIZE, true);
    }
  }
  uint64_t bit_vector::rank(uint64_t i, bool b) const {
    if (i > this->size()) { throw "shellinford::bit_vector::rank()"; }
    if (i == 0) { return 0; }
    i--;
    uint64_t q_large = i / LARGE_BLOCK_SIZE;
    uint64_t q_small = i / SMALL_BLOCK_SIZE;
    uint64_t r       = i % SMALL_BLOCK_SIZE;

    uint64_t rank = this->r_[q_large];
    if (!b) { rank = q_large * LARGE_BLOCK_SIZE - rank; }
    uint64_t begin = q_large * BLOCK_RATE;
    for (uint64_t j = begin; j < q_small; j++) {
      rank += rank64(this->v_[j], SMALL_BLOCK_SIZE, b);
    } 
    rank += rank64(this->v_[q_small], r + 1, b);
    return rank;
  }
  uint64_t bit_vector::select(uint64_t i, bool b) const {
    if (i >= this->size(b)) { throw "shellinford::bit_vector::select()"; }

    uint64_t left  = 0;
    uint64_t right = this->r_.size();
    while (left < right) {
      uint64_t pivot = (left + right) / 2;
      uint64_t rank  = this->r_[pivot];
      if (!b) { rank = pivot * LARGE_BLOCK_SIZE - rank; }
      if (i < rank) { right = pivot; }
      else          { left  = pivot + 1; }
    }
    right--;

    if (b) { i -= this->r_[right]; }
    else   { i -= right * LARGE_BLOCK_SIZE - this->r_[right]; }
    uint64_t j = right * BLOCK_RATE;
    while (1) {
      uint64_t rank = rank64(this->v_[j], SMALL_BLOCK_SIZE, b);
      if (i < rank) { break; }
      j++;
      i -= rank;
    }
    return j * SMALL_BLOCK_SIZE + select64(this->v_[j], i, b);
  }
  void bit_vector::write(ofstream &ofs) const {
    ofs.write((char *)&(this->size_), sizeof(uint64_t));
    ofs.write((char *)&(this->size1_), sizeof(uint64_t));

    uint64_t size = 0;
    size = this->v_.size();
    ofs.write((char *)&size, sizeof(uint64_t));
    for (uint64_t i = 0; i < size; i++) {
      ofs.write((char *)&(this->v_[i]), sizeof(uint64_t));
    }
    size = this->r_.size();
    ofs.write((char *)&size, sizeof(uint64_t));
    for (uint64_t i = 0; i < size; i++) {
      ofs.write((char *)&(this->r_[i]), sizeof(uint64_t));
    }
  }
  void bit_vector::write(const char *filename) const {
    ofstream ofs(filename, ios::out | ios::binary | ios::trunc);
    if (!ofs) { throw "shellinford::bit_vector::write()"; }
    this->write(ofs);
  }
  void bit_vector::read(ifstream &ifs) {
    ifs.read((char *)&(this->size_), sizeof(uint64_t));
    if (ifs.eof()) { throw "shellinford::bit_vector::read()"; }
    ifs.read((char *)&(this->size1_), sizeof(uint64_t));
    if (ifs.eof()) { throw "shellinford::bit_vector::read()"; }

    uint64_t size = 0;
    uint64_t x    = 0;
    ifs.read((char *)&size, sizeof(uint64_t));
    for (uint64_t i = 0; i < size; i++) {
      ifs.read((char *)&x, sizeof(uint64_t));
      if (ifs.eof()) { throw "shellinford::bit_vector::read()"; }
      this->v_.push_back(x);
    }
    ifs.read((char *)&size, sizeof(uint64_t));
    for (uint64_t i = 0; i < size; i++) {
      ifs.read((char *)&x, sizeof(uint64_t));
      if (ifs.eof()) { throw "shellinford::bit_vector::read()"; }
      this->r_.push_back(x);
    }
  }
  void bit_vector::read(const char *filename) {
    ifstream ifs(filename, ios::in | ios::binary);
    if (!ifs) { throw "shellinford::bit_vector::read()"; }
    this->read(ifs);
  }
}

