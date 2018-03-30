import unittest
from wurlitzer import pipes
import os, sys, sysconfig


# https://stackoverflow.com/a/14369968
def distutils_dir_name(dname):
    """Returns the name of a distutils build directory"""
    f = "{dirname}.{platform}-{version[0]}.{version[1]}"
    return f.format(dirname=dname,
                    platform=sysconfig.get_platform(),
                    version=sys.version_info)

sys.path.append(os.path.join('build', distutils_dir_name('lib')))
import hello


class HelloTest(unittest.TestCase):
  def test_hello(self):
    with pipes() as (out, err):
      hello.hello("world")
    self.assertEqual(out.read(), "Hello world!\n")
    self.assertEqual(err.read(), "")
    out.close()
    err.close()

  def test_raise_error(self):
    try:
      hello.raise_error()
    except Exception as e:
      self.assertEqual("something bad happened", str(e))
      self.assertEqual("<class 'hello.Error'>", str(type(e)))
