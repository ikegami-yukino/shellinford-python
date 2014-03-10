#include <cppunit/extensions/HelperMacros.h>
#include "shellinford_fm_index.h"
#include <string>
#include <algorithm>
#include <utility>
#include <vector>

using namespace CPPUNIT_NS;
using namespace std;
using namespace shellinford;
class test_fm_index : public TestFixture {
  CPPUNIT_TEST_SUITE(test_fm_index);
  CPPUNIT_TEST(size);
  CPPUNIT_TEST(docsize);
  CPPUNIT_TEST(get_rows);
  CPPUNIT_TEST(get_position);
  CPPUNIT_TEST(get_substring);
  CPPUNIT_TEST(get_document_id);
  CPPUNIT_TEST(get_document);
  CPPUNIT_TEST(get_position_boundary);
  CPPUNIT_TEST(get_substring_boundary);
  CPPUNIT_TEST(get_document_id_boundary);
  CPPUNIT_TEST(get_document_boundary);
  CPPUNIT_TEST_SUITE_END();

  string str;
  map<string, uint64_t> rd;
  vector<uint64_t> pd;
  vector<string> sd;
  vector<uint64_t> didd;
  vector<string> docd;
  fm_index fm;
  char end_marker;
  void size() {
    CPPUNIT_ASSERT_EQUAL(uint64_t(str.size()), fm.size());
  }
  void docsize() {
    CPPUNIT_ASSERT_EQUAL(uint64_t(docd.size()), fm.docsize());
  }
  void get_rows() {
    for (uint64_t i = 0;     i < fm.size(); i++) {
    for (uint64_t j = i + 1; j < fm.size(); j++) {
      string s = str.substr(i, j);
      CPPUNIT_ASSERT_EQUAL(rd[s], fm.get_rows(s));
    }
    }
  }
  void get_position() {
    for (uint64_t i = 0; i < fm.size(); i++) {
      CPPUNIT_ASSERT_EQUAL(pd[i], fm.get_position(i));
    }
  }
  void get_substring() {
    for (uint64_t i = 0; i < fm.size(); i++) {
      CPPUNIT_ASSERT_EQUAL(sd[i], fm.get_substring(i, fm.size()));
    }
  }
  void get_document_id() {
    for (uint64_t i = 0; i < fm.size(); i++) {
      CPPUNIT_ASSERT_EQUAL(didd[i], fm.get_document_id(i));
    }
  }
  void get_document() {
    for (uint64_t i = 0; i < fm.docsize(); i++) {
      CPPUNIT_ASSERT_EQUAL(docd[i], fm.get_document(i));
    }
  }
  void get_position_boundary() {
    try {
      fm.get_position(fm.size());
      CPPUNIT_FAIL("fm.get_position()");
    } catch (const char *s) { }
  }
  void get_substring_boundary() {
    try {
      fm.get_substring(fm.size(), 0);
      CPPUNIT_FAIL("fm.get_substring()");
    } catch (const char *s) { }
  }
  void get_document_id_boundary() {
    try {
      fm.get_document_id(fm.size());
      CPPUNIT_FAIL("fm.get_document_id()");
    } catch (const char *s) { }
  }
  void get_document_boundary() {
    try {
      fm.get_document(fm.docsize());
      CPPUNIT_FAIL("fm.get_document()");
    } catch (const char *s) { }
  }

public:
  void setUp() {
    end_marker = 1;
    docd.push_back("abracadabra");
    docd.push_back("mississippi");
    docd.push_back("abracadabra mississippi");
    vector<string>::const_iterator i = docd.begin();
    vector<string>::const_iterator e = docd.end();
    uint64_t did = 0;
    while (i != e) {
      str += *i;
      for (uint64_t j = 0; j < i->size(); j++){
        didd.push_back(did);
      }
      fm.push_back(*i);
      did++;
      i++;
    }
    didd.push_back(did);
    str += end_marker;
    fm.build(end_marker, 3);

    for (uint64_t i = 0; i < str.size(); i++) {
    for (uint64_t j = 1; j <= (str.size() - i); j++) {
      string s = str.substr(i, j);
      rd[s]++;
    }
    }

    vector<pair<string, uint64_t> > v;
    for (uint64_t i = 0; i < str.size(); i++) {
      string s = str.substr(i, str.size() - i) + str.substr(0, i);
      v.push_back(pair<string, uint64_t>(s, i));
    }
    sort(v.begin(), v.end());
    vector<pair<string, uint64_t> >::const_iterator i2 = v.begin();
    vector<pair<string, uint64_t> >::const_iterator e2 = v.end();
    while (i2 != e2) {
      pd.push_back(i2->second);
      i2++;
    }

    for (uint64_t i = 0; i < str.size(); i++) {
      sd.push_back(str.substr(i));
    }
  }
  void tearDown() {
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(test_fm_index);

