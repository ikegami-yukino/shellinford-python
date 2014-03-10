# -*- coding: utf-8 -*-
from nose.tools import assert_equal, assert_true
import shellinford
import tempfile
import os


class Test_FMIndex(object):

    def test_build(self):
        self.fm = shellinford.FMIndex()

        docs_list = ('a', 'b', 'c')
        self.fm.build(docs_list)
        assert_equal(self.fm.docsize(), 3)

        docs_dict = {'a': '1', 'b': '0', 'c': '2'}
        self.fm.build(docs_dict)
        assert_equal(self.fm.docsize(), 6)

        docs_generator = (str(i) for i in xrange(3))
        self.fm.build(docs_generator)
        assert_equal(self.fm.docsize(), 9)

    def test_search(self):
        self.fm = shellinford.FMIndex()
        docs_list = ('a', 'b', 'c')
        self.fm.build(docs_list)

        found_doc = self.fm.search('a').next()
        expected_result = shellinford.SEARCH_RESULT_FMINDEX(0, 1, 'a')
        assert_equal(found_doc, expected_result)

    def test_push_back(self):
        self.fm = shellinford.FMIndex()
        self.fm.push_back('a')
        self.fm.build()
        assert_equal(self.fm.docsize(), 1)

    def test_size(self):
        self.fm = shellinford.FMIndex()
        assert_equal(self.fm.size(), 0)
        self.fm.build(['a', 'b'])
        assert_equal(self.fm.size(), 3)

    def test_docsize(self):
        self.fm = shellinford.FMIndex()
        assert_equal(self.fm.docsize(), 0)
        self.fm.build(['a', 'b'])
        assert_equal(self.fm.docsize(), 2)

    def test_clear(self):
        self.fm = shellinford.FMIndex()
        self.fm.build(['a', 'b'])
        self.fm.clear()
        assert_equal(self.fm.size(), 0)
        assert_equal(self.fm.docsize(), 0)

    def test_write(self):
        self.fm = shellinford.FMIndex()
        filename = tempfile.mkstemp()[1]
        self.fm.build(['a', 'b'])
        self.fm.write(filename)
        assert_true(len(open(filename, 'r').read()) > 0)
        os.remove(filename)

    def test_read(self):
        self.fm = shellinford.FMIndex()
        filename = tempfile.mkstemp()[1]
        self.fm.build(['a', 'b'], filename)
        self.fm.clear()

        self.fm.read(filename)
        assert_equal(self.fm.docsize(), 2)
        found_doc = self.fm.search('a').next()
        expected_result = shellinford.SEARCH_RESULT_FMINDEX(0, 1, 'a')
        assert_equal(found_doc, expected_result)
        os.remove(filename)


class test_bit_vector(object):

    def test_set(self):
        self.bv = shellinford.bit_vector()
        self.bv.set(1)
        assert_equal(self.bv.size(), 2)

    def test_get(self):
        self.bv = shellinford.bit_vector()
        self.bv.set(100)
        assert_true(self.bv.get(100))

    def test_clear(self):
        self.bv = shellinford.bit_vector()
        self.bv.set(1)
        self.bv.clear()
        assert_equal(self.bv.size(), 0)

    def test_rank(self):
        self.bv = shellinford.bit_vector()
        self.bv.set(1)
        self.bv.set(1)
        self.bv.set(10)
        self.bv.set(100)
        self.bv.build()
        assert_equal(self.bv.rank(1), 0)

    def test_select(self):
        self.bv = shellinford.bit_vector()
        self.bv.set(1)
        self.bv.set(1)
        self.bv.set(10)
        self.bv.set(100)
        self.bv.build()
        assert_equal(self.bv.select(1), 10)

    def test_size(self):
        self.bv = shellinford.bit_vector()
        self.bv.set(1)
        self.bv.build()
        assert_equal(self.bv.size(), 2)
        assert_equal(self.bv.size(True), 1)

    def test_write(self):
        self.bv = shellinford.bit_vector()
        filename = tempfile.mkstemp()[1]
        self.bv.set(1)
        self.bv.build()
        self.bv.write(filename)
        assert_true(len(open(filename, 'r').read()) > 0)
        os.remove(filename)

    def test_read(self):
        self.bv = shellinford.bit_vector()
        filename = tempfile.mkstemp()[1]
        self.bv.set(100)
        self.bv.build()
        self.bv.write(filename)
        self.bv.clear()

        self.bv.read(filename)
        assert_true(self.bv.get(100))
        os.remove(filename)
