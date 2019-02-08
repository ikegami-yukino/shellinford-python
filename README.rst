shellinford
===========
|travis| |coveralls| |pyversion| |version| |license|

Shellinford is an implementation of a Wavelet Matrix/Tree succinct data structure for document retrieval.

It is based on `shellinford`_ C++ library.

.. _shellinford: https://github.com/echizentm/shellinford

NOTE: This module requires C++11 compiler

Installation
============

::

 $ pip install shellinford


Usage
=====

Create a new FM-index instance
-------------------------------

.. code:: python

 >>> import shellinford
 >>> fm = shellinford.FMIndex()


- shellinford.Shellinford([use_wavelet_tree=True, filename=None])

  - When given a filename, Shellinford loads FM-index data from the file


Build FM-index
-----------------------------

.. code:: python

 >>> fm.build(['Milky Holmes', 'Sherlock "Sheryl" Shellingford', 'Milky'], 'milky.fm')

- build([docs, filename])

  - When given a filename, Shellinford stores FM-index data to the file


Search word from FM-index
---------------------------------

.. code:: python

 >>> for doc in fm.search('Milky'):
 >>>     print('doc_id:', doc.doc_id)
 >>>     print('count:', doc.count)
 >>>     print('text:', doc.text)
 doc_id: 0
 count: [1]
 text: Milky Holmes
 doc_id: 2
 count: [1]
 text: Milky

 >>> for doc in fm.search(['Milky', 'Holmes']):
 >>>     print('doc_id:', doc.doc_id)
 >>>     print('count:', doc.count)
 >>>     print('text:', doc.text)
 doc_id: 1
 count: [1]
 text: Milky Holmes

- search(query, [_or=False, ignores=[]])

  - If `_or` = True, then "OR" search is executed, else "AND" search
  - Given `ignores`, "NOT" search is also executed
  - NOTE: The search function is available after FM-index is built or loaded


Count word from FM-index
---------------------------------

.. code:: python

 >>> fm.count('Milky'):
 2

 >>> fm.count(['Milky', 'Holmes']):
 1

- count(query, [_or=False])

  - If `_or` = True, then "OR" search is executed, else "AND" search
  - NOTE: The count function is available after FM-index is built or loaded
  - This function is slightly faster than the search function



Add a document
---------------------------------

.. code:: python

 >>> fm.push_back('Baritsu')

- push_back(doc)

  - NOTE: A document added by this method is not available to search until build


Read FM-index from a binary file
---------------------------------

.. code:: python

 >>> fm.read('milky_holmes.fm')

- read(path)


Write FM-index binary to a file
---------------------------------

.. code:: python

 >>> fm.write('milky_holmes.fm')

- write(path)


Check Whether FM-Index contains string
---------------------------------------

.. code:: python

 >>> 'baritsu' in fm


License
=========
- Wrapper code is licensed under the New BSD License.
- Bundled `shellinford`_ C++ library (c) 2012 echizen_tm is licensed under the New BSD License.


.. |travis| image:: https://travis-ci.org/ikegami-yukino/shellinford-python.svg?branch=master
    :target: https://travis-ci.org/ikegami-yukino/shellinford-python
    :alt: travis-ci.org

.. |coveralls| image:: https://coveralls.io/repos/ikegami-yukino/shellinford-python/badge.svg?branch=master&service=github
    :target: https://coveralls.io/github/ikegami-yukino/shellinford-python?branch=master
    :alt: coveralls.io

.. |pyversion| image:: https://img.shields.io/pypi/pyversions/shellinford.svg

.. |version| image:: https://img.shields.io/pypi/v/shellinford.svg
    :target: http://pypi.python.org/pypi/shellinford/
    :alt: latest version

.. |license| image:: https://img.shields.io/pypi/l/shellinford.svg
    :target: http://pypi.python.org/pypi/shellinford/
    :alt: license
