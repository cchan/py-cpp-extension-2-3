#!/usr/bin/env python
# encoding: utf-8

from setuptools import setup, Extension

hello_module = Extension('hello', sources=['src/hello.cpp'])

setup(name='hello',
      version='0.1.0',
      description='Hello world module for Py2/3 and C/C++.',
      author='Clive Chan',
      author_email='cc@clive.io',
      ext_modules=[hello_module])
