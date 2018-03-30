# Python 2/3 compatible C/C++ extension

This is a template to build from for C/C++ extensions that need to be compatible with both Python 2 and 3.


## Build

    python3 setup.py build

Output: `build/lib.*-3.5/hello.cpython-35m-*.so`

    python2 setup.py build

Output: `build/lib.*-2.7/hello.cpython-27m-*.so`


Then try `mv hello.cpp hello.c` and modifying `setup.py` to reflect `sources=['hello.c']`,
then repeating the above steps.


## Run

Python3:

    $ cd build/lib.*-3.5
    $ python3
    >>> import hello
    >>> hello.hello('world3')
    Hello, world3!
    >>> hello.raise_error()
    Traceback (most recent call last):
      File "<stdin>", line 1, in <module>
    hello.Error: something bad happened

Python2:

    $ cd build/lib.*-2.7
    $ python2
    >>> import hello
    >>> hello.hello('world2')
    Hello, world2!
    >>> hello.raise_error()
    Traceback (most recent call last):
      File "<stdin>", line 1, in <module>
    hello.Error: something bad happened


## Versions
    
- Windows 10 Linux Subsystem (4.4.0-43-Microsoft)
- Python 2.7.12 and 3.5.2
- x86_64-linux-gnu-gcc (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609


## References

- https://gist.github.com/physacco/2e1b52415f3a964ad2a542a99bebed8f/8ba2be17becb65015f505b87ed166f3163c14520
- https://docs.python.org/3/howto/cporting.html#module-initialization-and-state
- https://docs.python.org/2/extending/extending.html#intermezzo-errors-and-exceptions
