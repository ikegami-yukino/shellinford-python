shellinford
===========

Shellinford is an implementation of a Wavelet Matrix/Tree succinct data structure for document retrieval.

Based on `shellinford`_ C++ library.

.. _shellinford: https://code.google.com/p/shellinford/

Installation
============

::

 $ pip install shellinford


Usage
=====

Create a new FM-index instance
-----------------------------

::

 >>> import shellinford
 >>> fm = shellinford.FMIndex()


- shellinford.Shellinford([use_wavelet_tree=True, filename=None])

  - When given a filename, Shellinford loads FM-index data from the file


Build FM-index
-----------------------------

::

 >>> fm.build(['Milky Holmes', 'Sherlock "Sheryl" Shellingford'], 'milky.fm')

- build([docs, filename])

  - When given a filename, Shellinford stores FM-index data to the file


Search word from FM-index
---------------------------------

::

 >>> for doc in fm.search('Milky'):
 >>>     print 'doc_id:', doc.doc_id
 >>>     print 'count:', doc.count
 >>>     print 'text:', doc.text

- search(query)

  - NOTE: The search function is available after FM-index is built or loaded


Add a document
---------------------------------

::

 >>> fm.push_back('Baritsu')

- push_back(doc)

  - NOTE: A document added by this method is not available to search until build


Read FM-index from a binary file
---------------------------------

::

 >>> fm.read('milky_holmes.fm')

- read(path)


Write FM-index binary to a file
---------------------------------

::

 >>> fm.write('milky_holmes.fm')

- write(path)


License
=========
- Wrapper code is licensed under the New BSD License.
- Bundled `shellinford`_ C++ library (c) 2012 echizen_tm is licensed under the New BSD License.

