#include <cppunit/extensions/HelperMacros.h>
#include "shellinford_wavelet_matrix.h"
#include <cstring>

using namespace CPPUNIT_NS;
using namespace std;
using namespace shellinford;
class test_wavelet_matrix : public TestFixture {
  CPPUNIT_TEST_SUITE(test_wavelet_matrix);
  CPPUNIT_TEST(size);
  CPPUNIT_TEST(get);
  CPPUNIT_TEST(rank);
  CPPUNIT_TEST(select);
  CPPUNIT_TEST(rank_less_than);
  CPPUNIT_TEST(get_boundary);
  CPPUNIT_TEST(rank_boundary);
  CPPUNIT_TEST(select_boundary);
  CPPUNIT_TEST(rank_less_than_boundary);
  CPPUNIT_TEST_SUITE_END();

  const char *str;
  vector<vector<uint64_t> > rd;
  vector<vector<uint64_t> > sd;
  vector<vector<uint64_t> > td;
  wavelet_matrix<uint8_t> wm;
  void size() {
    CPPUNIT_ASSERT_EQUAL(uint64_t(strlen(str)), wm.size());
    for (uint64_t c = 0; c < 256; c++) {
      CPPUNIT_ASSERT_EQUAL(rd[c][wm.size()], wm.size(c));
    }
  }
  void get() {
    for (uint64_t i = 0; i < wm.size(); i++) {
      CPPUNIT_ASSERT_EQUAL(str[i], char(wm.get(i)));
    }
  }
  void rank() {
    for (uint64_t c = 0; c < 256; c++) {
      for (uint64_t i = 0; i <= wm.size(); i++) {
        CPPUNIT_ASSERT_EQUAL(rd[c][i], wm.rank(i, c));
      }
    }
  }
  void select() {
    for (uint64_t c = 0; c < 256; c++) {
      for (uint64_t i = 0; i < wm.size(c); i++) {
        CPPUNIT_ASSERT_EQUAL(sd[c][i], wm.select(i, c));
      }
    }
  }
  void rank_less_than() {
    for (uint64_t c = 0; c < 256; c++) {
      for (uint64_t i = 0; i <= wm.size(); i++) {
        CPPUNIT_ASSERT_EQUAL(td[c][i], wm.rank_less_than(i, c));
      }
    }
  }
  void get_boundary() {
    try {
      wm.get(strlen(str));
      CPPUNIT_FAIL("wm.get()");
    } catch (const char *s) { }
  }
  void rank_boundary() {
    for (uint64_t c = 0; c < 256; c++) {
      try {
        wm.rank(wm.size() + 1, c);
        CPPUNIT_FAIL("wm.rank()");
      } catch (const char *s) { }
    }
  }
  void select_boundary() {
    for (uint64_t c = 0; c < 256; c++) {
      try {
        wm.select(wm.size(c), c);
        CPPUNIT_FAIL("wm.select()");
      } catch (const char *s) { }
    }
  }
  void rank_less_than_boundary() {
    for (uint64_t c = 0; c < 256; c++) {
      try {
        wm.rank_less_than(wm.size() + 1, c);
        CPPUNIT_FAIL("wm.rank_less_than()");
      } catch (const char *s) { }
    }
  }

public:
  void setUp() {
    str = "abracadabra mississippi";
    wm.build(str);

    rd.assign(256, 0);
    sd.assign(256, 0);
    td.assign(256, 0);
    for (uint64_t c = 0; c < 256; c++) {
      rd[c].push_back(0);
      td[c].push_back(0);
    }

    for(uint64_t i = 0; str[i] != '\0'; i++) {
      for (uint64_t c = 0; c < 256; c++) {
        rd[c].push_back(rd[c][i]);
        td[c].push_back(td[c][i]);
        if (uint64_t(str[i]) == c) {
          rd[c][i + 1]++;
          sd[c].push_back(i);
        }
        if (uint64_t(str[i]) < c) {
          td[c][i + 1]++;
        }
      }
    }
  }
  void tearDown() {
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(test_wavelet_matrix);

