# This file was automatically generated by SWIG (http://www.swig.org).
# Version 3.0.0
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.


from sys import version_info
if version_info >= (2, 6, 0):
    def swig_import_helper():
        from os.path import dirname
        import imp
        fp = None
        try:
            fp, pathname, description = imp.find_module(
                '_shellinford', [dirname(__file__)])
        except ImportError:
            import _shellinford
            return _shellinford
        if fp is not None:
            try:
                _mod = imp.load_module(
                    '_shellinford', fp, pathname, description)
            finally:
                fp.close()
            return _mod
    _shellinford = swig_import_helper()
    items = 'items' if version_info >= (3, 0) else 'iteritems'
    del swig_import_helper
    del version_info
else:
    import _shellinford
try:
    _swig_property = property
except NameError:
    pass  # Python < 2.2 doesn't have 'property'.


def _swig_setattr_nondynamic(self, class_type, name, value, static=1):
    if (name == "thisown"):
        return self.this.own(value)
    if (name == "this"):
        if type(value).__name__ == 'SwigPyObject':
            self.__dict__[name] = value
            return
    method = class_type.__swig_setmethods__.get(name, None)
    if method:
        return method(self, value)
    if (not static):
        self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)


def _swig_setattr(self, class_type, name, value):
    return _swig_setattr_nondynamic(self, class_type, name, value, 0)


def _swig_getattr(self, class_type, name):
    if (name == "thisown"):
        return self.this.own()
    method = class_type.__swig_getmethods__.get(name, None)
    if method:
        return method(self)
    raise AttributeError(name)


def _swig_repr(self):
    try:
        strthis = "proxy of " + self.this.__repr__()
    except:
        strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__,
                             self.__class__.__name__, strthis,)

try:
    _object = object
    _newclass = 1
except AttributeError:
    class _object:
        pass
    _newclass = 0


class SwigPyIterator(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(
        self, SwigPyIterator, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, SwigPyIterator, name)

    def __init__(self, *args, **kwargs):
        raise AttributeError("No constructor defined - class is abstract")
    __repr__ = _swig_repr
    __swig_destroy__ = _shellinford.delete_SwigPyIterator
    __del__ = lambda self: None

    def value(self):
        return _shellinford.SwigPyIterator_value(self)

    def incr(self, n=1):
        return _shellinford.SwigPyIterator_incr(self, n)

    def decr(self, n=1):
        return _shellinford.SwigPyIterator_decr(self, n)

    def distance(self, *args):
        return _shellinford.SwigPyIterator_distance(self, *args)

    def equal(self, *args):
        return _shellinford.SwigPyIterator_equal(self, *args)

    def copy(self):
        return _shellinford.SwigPyIterator_copy(self)

    def next(self):
        return _shellinford.SwigPyIterator_next(self)

    def __next__(self):
        return _shellinford.SwigPyIterator___next__(self)

    def previous(self):
        return _shellinford.SwigPyIterator_previous(self)

    def advance(self, *args):
        return _shellinford.SwigPyIterator_advance(self, *args)

    def __eq__(self, *args):
        return _shellinford.SwigPyIterator___eq__(self, *args)

    def __ne__(self, *args):
        return _shellinford.SwigPyIterator___ne__(self, *args)

    def __iadd__(self, *args):
        return _shellinford.SwigPyIterator___iadd__(self, *args)

    def __isub__(self, *args):
        return _shellinford.SwigPyIterator___isub__(self, *args)

    def __add__(self, *args):
        return _shellinford.SwigPyIterator___add__(self, *args)

    def __sub__(self, *args):
        return _shellinford.SwigPyIterator___sub__(self, *args)

    def __iter__(self):
        return self
SwigPyIterator_swigregister = _shellinford.SwigPyIterator_swigregister
SwigPyIterator_swigregister(SwigPyIterator)


class MapIntInt(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(
        self, MapIntInt, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, MapIntInt, name)
    __repr__ = _swig_repr

    def iterator(self):
        return _shellinford.MapIntInt_iterator(self)

    def __iter__(self):
        return self.iterator()

    def __nonzero__(self):
        return _shellinford.MapIntInt___nonzero__(self)

    def __bool__(self):
        return _shellinford.MapIntInt___bool__(self)

    def __len__(self):
        return _shellinford.MapIntInt___len__(self)

    def iterkeys(self):
        return self.key_iterator()

    def itervalues(self):
        return self.value_iterator()

    def iteritems(self):
        return self.iterator()

    def __getitem__(self, *args):
        return _shellinford.MapIntInt___getitem__(self, *args)

    def __delitem__(self, *args):
        return _shellinford.MapIntInt___delitem__(self, *args)

    def has_key(self, *args):
        return _shellinford.MapIntInt_has_key(self, *args)

    def keys(self):
        return _shellinford.MapIntInt_keys(self)

    def values(self):
        return _shellinford.MapIntInt_values(self)

    def items(self):
        return _shellinford.MapIntInt_items(self)

    def __contains__(self, *args):
        return _shellinford.MapIntInt___contains__(self, *args)

    def key_iterator(self):
        return _shellinford.MapIntInt_key_iterator(self)

    def value_iterator(self):
        return _shellinford.MapIntInt_value_iterator(self)

    def __setitem__(self, *args):
        return _shellinford.MapIntInt___setitem__(self, *args)

    def asdict(self):
        return _shellinford.MapIntInt_asdict(self)

    def __init__(self, *args):
        this = _shellinford.new_MapIntInt(*args)
        try:
            self.this.append(this)
        except:
            self.this = this

    def empty(self):
        return _shellinford.MapIntInt_empty(self)

    def size(self):
        return _shellinford.MapIntInt_size(self)

    def clear(self):
        return _shellinford.MapIntInt_clear(self)

    def swap(self, *args):
        return _shellinford.MapIntInt_swap(self, *args)

    def get_allocator(self):
        return _shellinford.MapIntInt_get_allocator(self)

    def begin(self):
        return _shellinford.MapIntInt_begin(self)

    def end(self):
        return _shellinford.MapIntInt_end(self)

    def rbegin(self):
        return _shellinford.MapIntInt_rbegin(self)

    def rend(self):
        return _shellinford.MapIntInt_rend(self)

    def count(self, *args):
        return _shellinford.MapIntInt_count(self, *args)

    def erase(self, *args):
        return _shellinford.MapIntInt_erase(self, *args)

    def find(self, *args):
        return _shellinford.MapIntInt_find(self, *args)

    def lower_bound(self, *args):
        return _shellinford.MapIntInt_lower_bound(self, *args)

    def upper_bound(self, *args):
        return _shellinford.MapIntInt_upper_bound(self, *args)
    __swig_destroy__ = _shellinford.delete_MapIntInt
    __del__ = lambda self: None
MapIntInt_swigregister = _shellinford.MapIntInt_swigregister
MapIntInt_swigregister(MapIntInt)


class fm_index(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(
        self, fm_index, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, fm_index, name)
    __repr__ = _swig_repr

    def __init__(self, use_wavelet_tree=False):
        this = _shellinford.new_fm_index(use_wavelet_tree)
        try:
            self.this.append(this)
        except:
            self.this = this
    __swig_destroy__ = _shellinford.delete_fm_index
    __del__ = lambda self: None

    def clear(self):
        return _shellinford.fm_index_clear(self)

    def push_back(self, *args):
        return _shellinford.fm_index_push_back(self, *args)

    def build(self, end_marker=1, ddic=64, is_msg=False):
        return _shellinford.fm_index_build(self, end_marker, ddic, is_msg)

    def size(self):
        return _shellinford.fm_index_size(self)

    def docsize(self):
        return _shellinford.fm_index_docsize(self)

    def get_rows(self, *args):
        return _shellinford.fm_index_get_rows(self, *args)

    def get_position(self, *args):
        return _shellinford.fm_index_get_position(self, *args)

    def get_substring(self, *args):
        return _shellinford.fm_index_get_substring(self, *args)

    def get_document_id(self, *args):
        return _shellinford.fm_index_get_document_id(self, *args)

    def search(self, *args):
        return _shellinford.fm_index_search(self, *args)

    def get_document(self, *args):
        return _shellinford.fm_index_get_document(self, *args)

    def write(self, *args):
        return _shellinford.fm_index_write(self, *args)

    def read(self, *args):
        return _shellinford.fm_index_read(self, *args)
fm_index_swigregister = _shellinford.fm_index_swigregister
fm_index_swigregister(fm_index)


class bwt(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(
        self, bwt, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, bwt, name)
    __repr__ = _swig_repr

    def __init__(self):
        this = _shellinford.new_bwt()
        try:
            self.this.append(this)
        except:
            self.this = this
    __swig_destroy__ = _shellinford.delete_bwt
    __del__ = lambda self: None

    def clear(self):
        return _shellinford.bwt_clear(self)

    def build(self, *args):
        return _shellinford.bwt_build(self, *args)

    @property
    def size(self):
        return _shellinford.bwt_size(self)

    @property
    def head(self):
        return _shellinford.bwt_head(self)

    def get(self, *args):
        return _shellinford.bwt_get(self, *args)
bwt_swigregister = _shellinford.bwt_swigregister
bwt_swigregister(bwt)


class bit_vector(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(
        self, bit_vector, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, bit_vector, name)
    __repr__ = _swig_repr

    def __init__(self):
        this = _shellinford.new_bit_vector()
        try:
            self.this.append(this)
        except:
            self.this = this
    __swig_destroy__ = _shellinford.delete_bit_vector
    __del__ = lambda self: None

    def clear(self):
        return _shellinford.bit_vector_clear(self)

    def get(self, *args):
        return _shellinford.bit_vector_get(self, *args)

    def set(self, *args):
        return _shellinford.bit_vector_set(self, *args)

    def build(self):
        return _shellinford.bit_vector_build(self)

    def size(self, *args):
        return _shellinford.bit_vector_size(self, *args)

    def rank(self, *args):
        return _shellinford.bit_vector_rank(self, *args)

    def select(self, *args):
        return _shellinford.bit_vector_select(self, *args)

    def write(self, *args):
        return _shellinford.bit_vector_write(self, *args)

    def read(self, *args):
        return _shellinford.bit_vector_read(self, *args)
bit_vector_swigregister = _shellinford.bit_vector_swigregister
bit_vector_swigregister(bit_vector)
cvar = _shellinford.cvar
SMALL_BLOCK_SIZE = cvar.SMALL_BLOCK_SIZE
LARGE_BLOCK_SIZE = cvar.LARGE_BLOCK_SIZE
BLOCK_RATE = cvar.BLOCK_RATE


from collections import namedtuple
from operator import add
from functools import reduce
SEARCH_RESULT = namedtuple('FM_index', 'doc_id count text')


class FMIndex(object):

    def __init__(self, use_wavelet_tree=False, filename=None):
        self.fm = fm_index(use_wavelet_tree)
        if filename:
            self.fm.read(filename)

    def build(self, docs=None, filename=None):
        """Build FM-index
        Params:
            <iterator> | <generator> docs
            <str> filename
        """
        if docs:
            if hasattr(docs, items):
                for (idx, doc) in sorted(getattr(docs, items)(),
                                         key=lambda x: x[0]):
                    self.fm.push_back(doc)
            else:
                for doc in filter(bool, docs):
                    self.fm.push_back(doc)
        self.fm.build()
        if filename:
            self.fm.write(filename)

    def _merge_search_result(self, search_results, _or=False):
        """Merge of filter search results
        Params:
            <str> | <Sequential> query
            <bool> _or
        Return:
            <list> computed_dids
        """
        all_docids = reduce(add, [list(x.keys()) for x in search_results])
        if _or:
            return sorted(set(all_docids), key=all_docids.index)
        return [docid for docid in set(all_docids) if all_docids.count(docid) > 1]

    def search(self, query, _or=False, ignores=[]):
        """Search word from FM-index
        Params:
            <str> | <Sequential> query
            <bool> _or
            <list <str> > ignores
        Return:
            <list>SEARCH_RESULT(<int> document_id,
                                <list <int> > counts
                                <str> doc)
        """
        if isinstance(query, str):
            dids = MapIntInt({})
            self.fm.search(query, dids)
            dids = dids.asdict()
            result = []
            for did in sorted(dids.keys()):
                doc = self.fm.get_document(did)
                if not any(ignore in doc for ignore in ignores):
                    count = dids[did]
                    result.append(SEARCH_RESULT(int(did), [count], doc))
            return result

        search_results = []
        for q in query:
            dids = MapIntInt({})
            self.fm.search(q, dids)
            search_results.append(dids.asdict())
        merged_dids = self._merge_search_result(search_results, _or)
        result = []
        for did in merged_dids:
            doc = self.fm.get_document(did)
            if not any(ignore in doc for ignore in ignores):
                counts = map(lambda x: int(x.pop(did, 0)), search_results)
                result.append(SEARCH_RESULT(int(did), list(counts), doc))
        return result

    def push_back(self, doc):
        """Add document to FM-index
        Params:
            <str> doc
        """
        if doc:
            self.fm.push_back(doc)

    def __contains__(self, query):
        """Whether string is in FM-index
        Params:
            <str> query
        Return:
            <bool>
        """
        return bool(self.search(query))

    @property
    def size(self):
        return self.fm.size()

    def __len__(self):
        return self.fm.size()

    @property
    def docsize(self):
        return self.fm.docsize()

    def clear(self):
        self.fm.clear()

    def read(self, filename):
        self.fm.read(filename)

    def write(self, filename):
        self.fm.write(filename)

# This file is compatible with both classic and new-style classes.
