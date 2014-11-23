#include <cppunit/extensions/HelperMacros.h>
#include "shellinford_bit_vector.h"
#include <vector>

using namespace CPPUNIT_NS;
using namespace std;
using namespace shellinford;
class test_bit_vector : public TestFixture {
  CPPUNIT_TEST_SUITE(test_bit_vector);
  CPPUNIT_TEST(size);
  CPPUNIT_TEST(get);
  CPPUNIT_TEST(rank);
  CPPUNIT_TEST(select);
  CPPUNIT_TEST(get_boundary);
  CPPUNIT_TEST(rank_boundary);
  CPPUNIT_TEST(select_boundary);
  CPPUNIT_TEST_SUITE_END();

  vector<uint64_t> values;
  bit_vector bv1;
  bit_vector bv0;
  void size() {
    CPPUNIT_ASSERT_EQUAL(values.back() + 1, bv1.size());
    CPPUNIT_ASSERT_EQUAL(uint64_t(values.size()), bv1.size(true));
    CPPUNIT_ASSERT_EQUAL(values.back() + 1, bv0.size());
    CPPUNIT_ASSERT_EQUAL(uint64_t(values.size()), bv0.size(false));
  }
  void get() {
    vector<uint64_t>::const_iterator i = values.begin();
    vector<uint64_t>::const_iterator e = values.end();
    while (i != e) {
      uint64_t v = *i;
      CPPUNIT_ASSERT_EQUAL(true , bv1.get(v));
      CPPUNIT_ASSERT_EQUAL(false, bv0.get(v));
      i++;
    }
  }
  void rank() {
    vector<uint64_t>::const_iterator i = values.begin();
    vector<uint64_t>::const_iterator e = values.end();
    uint64_t ct = 0;
    while (i != e) {
      uint64_t v = *i;
      CPPUNIT_ASSERT_EQUAL(ct, bv1.rank(v, true));
      CPPUNIT_ASSERT_EQUAL(ct, bv0.rank(v, false));
      ct++;
      i++;
    }
  }
  void select() {
    vector<uint64_t>::const_iterator i = values.begin();
    vector<uint64_t>::const_iterator e = values.end();
    uint64_t ct = 0;
    while (i != e) {
      uint64_t v = *i;
      CPPUNIT_ASSERT_EQUAL(v, bv1.select(ct, true));
      CPPUNIT_ASSERT_EQUAL(v, bv0.select(ct, false));
      ct++;
      i++;
    }
  }


  void get_boundary() {
    try {
      bv1.get(bv1.size());
      CPPUNIT_FAIL("bv1.get()");
    } catch (const char *s) { }
    try {
      bv0.get(bv0.size());
      CPPUNIT_FAIL("bv0.get()");
    } catch (const char *s) { }
  }
  void rank_boundary() {
    try {
      bv1.rank(bv1.size() + 1, true);
      CPPUNIT_FAIL("bv1.rank(true)");
    } catch (const char *s) { }
    try {
      bv1.rank(bv1.size() + 1, false);
      CPPUNIT_FAIL("bv1.rank(false)");
    } catch (const char *s) { }
    try {
      bv0.rank(bv0.size() + 1, true);
      CPPUNIT_FAIL("bv0.rank(true)");
    } catch (const char *s) { }
    try {
      bv0.rank(bv0.size() + 1, false);
      CPPUNIT_FAIL("bv0.rank(false)");
    } catch (const char *s) { }
  }
  void select_boundary() {
    try {
      bv1.select(bv1.size(true), true);
      CPPUNIT_FAIL("bv1.select(true)");
    } catch (const char *s) { }
    try {
      bv1.select(bv1.size(false), false);
      CPPUNIT_FAIL("bv1.select(false)");
    } catch (const char *s) { }
    try {
      bv0.select(bv0.size(true), true);
      CPPUNIT_FAIL("bv0.select(true)");
    } catch (const char *s) { }
    try {
      bv0.select(bv0.size(false), false);
      CPPUNIT_FAIL("bv0.select(false)");
    } catch (const char *s) { }
  }

public:
  void setUp() {
    values.push_back(0);
    values.push_back(511);
    values.push_back(512);
    values.push_back(1000);
    values.push_back(2000);
    values.push_back(3000);

    for (uint64_t i = 0; i <= values.back(); i++) {
      bv0.set(i, true);
    }

    vector<uint64_t>::const_iterator i = values.begin();
    vector<uint64_t>::const_iterator e = values.end();
    while (i != e) {
      bv1.set(*i, true);
      bv0.set(*i, false);
      i++;
    }
    bv1.build();
    bv0.build();
  }
  void tearDown() {
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(test_bit_vector);

