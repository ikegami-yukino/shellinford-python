#ifndef SHELLINFORD_FM_INDEX
#define SHELLINFORD_FM_INDEX

#include "shellinford_wavelet_tree.h"
#include "shellinford_wavelet_matrix.h"
#include <string>
#include <map>

namespace shellinford {
  class fm_index {
    succinct_vector<uint8_t> *sv_;
    bit_vector               doctails_;
    std::vector<uint64_t>    posdic_;
    std::vector<uint64_t>    idic_;
    uint64_t                 ddic_;
    uint64_t                 head_;
    uint64_t                 rlt_[256];
    std::string              substr_;

  public:
    fm_index(bool use_wavelet_tree = false);
    ~fm_index();
    void clear();
    void push_back(const std::string &doc);
    void build(char end_marker = 1, uint64_t ddic = 64,
               bool is_msg = false);
    uint64_t size() const { return this->sv_->size(); }
    uint64_t docsize() const { return this->doctails_.size(true); }
    uint64_t get_rows(const std::string &key) const;
    uint64_t get_rows(const std::string &key,
                      uint64_t &first, uint64_t &last) const;
    uint64_t get_position(uint64_t i) const;
    const std::string &get_substring(uint64_t pos, uint64_t len);
    uint64_t get_document_id(uint64_t pos) const;
    void search(const std::string &key,
                std::map<uint64_t, uint64_t> &dids) const;
    const std::string &get_document(uint64_t did);
    void write(std::ofstream &ofs) const;
    void write(const char *filename) const;
    void read(std::ifstream &ifs);
    void read(const char *filename);
  };

  class bwt {
    const char            *str_;
    uint64_t              size_;
    uint64_t              head_;
    std::vector<uint64_t> sa_;
    void sort(int64_t begin, int64_t end, uint64_t depth);
    uint8_t sa2char(uint64_t i, uint64_t depth) const;

  public:
    bwt();
    ~bwt();
    void clear();
    void build(const char *str);
    uint64_t size() const { return this->size_; }
    uint64_t head() const { return this->head_; }
    char get(uint64_t i) const;
    void get(std::string &str) const;
  };
}

#endif

