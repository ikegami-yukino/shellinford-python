# -*- coding: utf-8 -*-
from setuptools import setup, Extension, find_packages
import glob

shellinford_cc = glob.glob('shellinford/src/*.cc')
shellinford_headers = glob.glob('shellinford/src/*.h')
setup (
        name = 'shellinford',
        version = '0.1',
        author = "Yukino Ikegami",
        author_email='yukinoik@icloud.com',
        url='https://github.com/ikegami-yukino/shellinford-python',
        description = """Wavelet Matrix/Tree succinct data structure for text search (using shellinford C++ library)""",
        long_description = open('README.rst').read() + "\n\n" + open('CHANGES.rst').read(),

        py_modules = ["shellinford"],
        ext_modules = [
            Extension('_shellinford',
            sources=['shellinford_wrap.cxx'] + shellinford_cc,
            include_dirs=['shellinford/src'],
            depends=shellinford_headers,
            language = "c++"
            ),
        ],

        headers=shellinford_headers,
        packages=find_packages(),

        classifiers=[
            'Development Status :: 3 - Alpha',
            'Intended Audience :: Developers',
            'Intended Audience :: Science/Research',
            'License :: OSI Approved :: BSD License',
            'Programming Language :: C++',
            'Programming Language :: Python :: 2.6',
            'Programming Language :: Python :: 2.7',
            'Topic :: Software Development :: Libraries :: Python Modules',
            'Topic :: Scientific/Engineering :: Information Analysis',
            'Topic :: Text Processing :: Linguistic',
            ],
        )
