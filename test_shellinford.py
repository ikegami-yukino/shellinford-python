# -*- coding: utf-8 -*-
from nose.tools import assert_equal, assert_true, nottest
import shellinford
from shellinford.shellinford import SEARCH_RESULT
import tempfile
import os
from sys import version_info


class Test_FMIndex(object):

    def test_build(self):
        fm = shellinford.FMIndex()

        docs_list = ('a', 'b', 'c')
        fm.build(docs_list)
        assert_equal(fm.docsize, 3)

        docs_dict = {'a': '1', 'b': '0', 'c': '2'}
        fm.build(docs_dict)
        assert_equal(fm.docsize, 6)

        if version_info >= (3, 0, 0):
            docs_generator = (str(i) for i in range(3))
        else:
            docs_generator = (str(i) for i in xrange(3))
        fm.build(docs_generator)
        assert_equal(fm.docsize, 9)

    def test_search(self):
        fm = shellinford.FMIndex()
        docs_list = ('ab', 'bc', 'cd')
        fm.build(docs_list)

        params = [dict(query='a'),
                  dict(query=['a', 'b'], _or=False),
                  dict(query='a', _or=False, ignores=['c']),
                  dict(query=['a', 'd'], _or=True),
                  dict(query=['a', 'd'], _or=True, ignores=['c'])]
        desireds = [[SEARCH_RESULT(0, [1], 'ab')],
                    [SEARCH_RESULT(0, [1, 1], 'ab')],
                    [SEARCH_RESULT(0, [1], 'ab')],
                    [SEARCH_RESULT(0, [1, 0], 'ab'),
                     SEARCH_RESULT(2, [0, 1], 'cd')],
                    [SEARCH_RESULT(0, [1, 0], 'ab')]]
        for (param, desired) in zip(params, desireds):
            actual = fm.search(**param)
            assert_equal(list(actual), desired)

    def test_push_back(self):
        fm = shellinford.FMIndex()
        fm.push_back('a')
        fm.build()
        assert_equal(fm.docsize, 1)

    def test_size(self):
        fm = shellinford.FMIndex()
        assert_equal(fm.size, 0)
        fm.build(['a', 'b'])
        assert_equal(fm.size, 3)
        assert_equal(len(fm), 3)

    def test_docsize(self):
        fm = shellinford.FMIndex()
        assert_equal(fm.docsize, 0)
        fm.build(['a', 'b'])
        assert_equal(fm.docsize, 2)

    def test_clear(self):
        fm = shellinford.FMIndex()
        fm.build(['a', 'b'])
        fm.clear()
        assert_equal(fm.size, 0)
        assert_equal(fm.docsize, 0)

    def test_write(self):
        fm = shellinford.FMIndex()
        try:
            filename = tempfile.mkstemp()[1]
            fm.build(['a', 'b'])
            fm.write(filename)
            assert_true(len(open(filename, 'r').read()) > 0)
        finally:
            os.remove(filename)

    def test_read(self):
        fm = shellinford.FMIndex()
        try:
            filename = tempfile.mkstemp()[1]
            fm.build(['a', 'b'], filename)
            fm.clear()

            fm.read(filename)
            assert_equal(fm.docsize, 2)
            found_doc = fm.search('a')
            expected_result = SEARCH_RESULT(0, [1], 'a')
            assert_equal(found_doc[0], expected_result)
        finally:
            os.remove(filename)

    def test___init__(self):
        fm = shellinford.FMIndex()
        try:
            filename = tempfile.mkstemp()[1]
            fm.build(['a', 'b'])
            fm.write(filename)
            del fm
            fm = shellinford.FMIndex(filename=filename)
            assert_equal(fm.docsize, 2)
            found_doc = fm.search('a')
            expected_result = SEARCH_RESULT(0, [1], 'a')
            assert_equal(found_doc[0], expected_result)
        finally:
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


class test_bwt(object):

    def test_clear(self):
        bwt = shellinford.bwt()
        bwt.build('iroha')
        bwt.clear()
        assert_equal(bwt.size, 0)

    def test_build(self):
        bwt = shellinford.bwt()
        assert_equal(bwt.size, 0)
        bwt.build('iroha')
        assert_equal(bwt.size, 5)

    def test_size(self):
        bwt = shellinford.bwt()
        assert_equal(bwt.size, 0)

    def test_head(self):
        bwt = shellinford.bwt()
        assert_equal(bwt.head, 0)

    @nottest
    def test_get(self):
        pass
