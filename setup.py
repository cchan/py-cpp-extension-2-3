#!/usr/bin/env python
# encoding: utf-8

from distutils.core import setup, Extension

hello_module = Extension('hello', sources=['hello.cpp'])

setup(name='hello',
      version='0.1.0',
      description='Hello world module for Py2/3 and C/C++.',
      ext_modules=[hello_module])
