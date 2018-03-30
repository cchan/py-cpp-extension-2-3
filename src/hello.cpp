/*
 * A Hello World Python extension that works in both Python2 and Python3, and both C and C++.
 */


#include <stdio.h>
#include "Python.h"

struct module_state {
    PyObject *error;
};

#if PY_MAJOR_VERSION >= 3
#define GETSTATE(m) ((struct module_state*)PyModule_GetState(m))
#else
#define GETSTATE(m) (&_state)
static struct module_state _state;
#endif

/*
 *Module method definitions
 */

static PyObject *
hello(PyObject *self, PyObject *args){
    const char* name;
    if (!PyArg_ParseTuple(args, "s", &name)) {
        return NULL;
    }

    printf("Hello %s!\n", name);
    Py_RETURN_NONE;
}

static PyObject *
raise_error(PyObject *m) {
    struct module_state *st = GETSTATE(m);
    PyErr_SetString(st->error, "something bad happened");
    return NULL;
}


/*
 * Method definition object for this extension, these argumens mean:
 * ml_name: The name of the method
 * ml_meth: Function pointer to the method implementation
 * ml_flags: Flags indicating special features of this method, such as
 *          accepting arguments, accepting keyword arguments, being a
 *          class method, or being a static method of a class.
 * ml_doc:  Contents of this method's docstring
 */

static PyMethodDef hello_methods[] = {
    {"hello", (PyCFunction)hello, METH_VARARGS, "Print 'hello xxx' from a method defined in a C extension."},
    {"raise_error", (PyCFunction)raise_error, METH_NOARGS, NULL},
    {NULL, NULL}
};

#if PY_MAJOR_VERSION >= 3

static int hello_traverse(PyObject *m, visitproc visit, void *arg) {
    Py_VISIT(GETSTATE(m)->error);
    return 0;
}

static int hello_clear(PyObject *m) {
    Py_CLEAR(GETSTATE(m)->error);
    return 0;
}

/* Module definition
 * The arguments of this structure tell Python what to call your extension,
 * what it's methods are and where to look for it's method definitions
 */

static struct PyModuleDef moduledef = {
        PyModuleDef_HEAD_INIT,
        "hello",
        "A Python module that prints 'hello world' from C code.",
        sizeof(struct module_state),
        hello_methods,
        NULL,
        hello_traverse,
        hello_clear,
        NULL
};

#define INITERROR return NULL

/* Module initialization
 * Python calls this function when importing your extension. It is important
 * that this function is named PyInit_[[your_module_name]] exactly, and matches
 * the name keyword argument in setup.py's setup() call.
 */

PyMODINIT_FUNC
PyInit_hello(void)

#else
#define INITERROR return

PyMODINIT_FUNC
inithello(void)
#endif
{
#if PY_MAJOR_VERSION >= 3
    PyObject *module = PyModule_Create(&moduledef);
#else
    PyObject *module = Py_InitModule("hello", hello_methods);
#endif

    if (module == NULL)
        INITERROR;
    struct module_state *st = GETSTATE(module);

    st->error = PyErr_NewException("hello.Error", NULL, NULL);
    if (st->error == NULL) {
        Py_DECREF(module);
        INITERROR;
    }

#if PY_MAJOR_VERSION >= 3
    return module;
#endif
}
