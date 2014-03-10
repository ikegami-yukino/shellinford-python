#ifndef SHELLINFORD_SUCCINCT_VECTOR
#define SHELLINFORD_SUCCINCT_VECTOR

#include <stdint.h>
#include <vector>
#include <fstream>

namespace shellinford {
  // succinct_vector<T> is template class.
  // T must be uint8_t, uint16_t, uint32_t or uint64_t.
  template<class T>
  class succinct_vector {
  public:
    virtual ~succinct_vector(){};
    virtual void clear() = 0;
    virtual void build(const char *s) = 0;
    virtual void build(std::vector<T> &v) = 0;
    virtual uint64_t bitsize() const = 0;
    virtual uint64_t size() const = 0;
    virtual uint64_t size(T c) const = 0;
    virtual T get(uint64_t i) const = 0;
    virtual uint64_t rank(uint64_t i, T c) const = 0;
    virtual uint64_t select(uint64_t i, T c) const = 0;
    virtual uint64_t rank_less_than(uint64_t i, T c) const = 0;
    virtual void write(std::ofstream &ofs) const = 0;
    virtual void write(const char *filename) const = 0;
    virtual void read(std::ifstream &ifs) = 0;
    virtual void read(const char *filename) = 0;
  };

  template<class T>
  bool uint2bit(T c, uint64_t i) {
    return ((c >> (sizeof(T) * 8 - 1 - i)) & 0x1ULL) == 0x1ULL;
  }
}

#endif

