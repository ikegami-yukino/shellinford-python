# -*- coding: utf-8 -*-
import os
import re
from setuptools import setup, Extension
import glob


shellinford_cc = glob.glob('shellinford_cpp/src/*.cc')
shellinford_headers = glob.glob('shellinford_cpp/src/*.h')
with open(os.path.join('shellinford', '__init__.py'), 'r') as f:
    version = re.compile(
            r".*__version__ = '(.*?)'", re.S).match(f.read()).group(1)

setup (
    name = 'shellinford',
    version = version,
    author = "Yukino Ikegami",
    author_email='yukinoik@icloud.com',
    url='https://github.com/ikegami-yukino/shellinford-python',
    description = """Wavelet Matrix/Tree succinct data structure for full text search (using shellinford C++ library)""",
    long_description = open('README.rst').read() + "\n" + open('CHANGES.rst').read(),
    keywords = ['full text search', 'FM-index', 'Wavelet Matrix'],

    ext_modules = [
        Extension(
            '_shellinford',
            sources=['shellinford_wrap.cxx'] + shellinford_cc,
            include_dirs=['shellinford_cpp/src'],
            depends=shellinford_headers,
            language = "c++"
        ),
    ],

    headers=shellinford_headers,
    packages=["shellinford"],

    classifiers=[
        'Development Status :: 3 - Alpha',
        'Intended Audience :: Developers',
        'Intended Audience :: Science/Research',
        'License :: OSI Approved :: BSD License',
        'Programming Language :: C++',
        'Programming Language :: Python :: 2.6',
        'Programming Language :: Python :: 2.7',
        'Programming Language :: Python :: 3.3',
        'Programming Language :: Python :: 3.4',
        'Topic :: Software Development :: Libraries :: Python Modules',
        'Topic :: Scientific/Engineering :: Information Analysis',
        'Topic :: Text Processing :: Linguistic',
        'Topic :: Text Processing :: Indexing'
        ],
)
