/*
Including python headers
*/

#define PY_SSIZE_T_CLEAN
#ifdef __linux__
#include <Python.h>
#elif defined(__APPLE__)
#include <Python.h>
#elif defined(_WIN32) || defined(_WIN64)
#warning "TODO";
#endif

#include "libarr.h"

static PyObject* int_to_pylist(const int *arr, int n)
{
    PyObject *plist, *pitem;

    plist = PyList_New(n);
    if (!plist)
        return NULL;

    for (int i = 0; i < n; i++)
    {
        pitem = PyLong_FromLong((long) arr[i]);
        if (!pitem)
        {
            Py_DECREF(plist);
            return NULL;
        }

        PyList_SET_ITEM(plist, i, pitem);
    }

    return plist;
}

static PyObject *py_arr_lshift(PyObject *self, PyObject *args)
{
    PyObject *seq;
    PyObject *item;

    int shift;

    if (!PyArg_ParseTuple(args, "Oi", &seq, &shift))
        return NULL;

    seq = PySequence_Fast(seq, "Argument must be iterable");
    if (!seq)
        return NULL;
    
    int n = PySequence_Fast_GET_SIZE(seq);

    int *arr = malloc(n * sizeof(int));

    if (arr == NULL)
    {
        Py_DecRef(seq);
        return NULL;
    }

    // Copying python list in array
    for (int i = 0; i < n; i++)
    {
        item = PySequence_Fast_GET_ITEM(seq, i);
        
        if (item == NULL)
        {
            Py_DecRef(seq);
            free(arr);
            return NULL;
        }

        if (PyLong_Check(item) == -1)
        {
            PyErr_SetString(PyExc_TypeError, "Bad list given");
            Py_DecRef(seq);
            free(arr);
            return NULL;
        }

        arr[i] = PyLong_AsLong(item);
    }

    int res = arr_lshift(arr, n, shift);

    PyObject *new_list = NULL;

    if (res < 0)
        PyErr_SetString(PyExc_TypeError, "Array shift error");
    else
        new_list = int_to_pylist(arr, n);


    Py_DecRef(seq);
    free(arr);

    return new_list;
}

static PyObject *py_arr_nonsqr(PyObject *self, PyObject *args)
{
    PyObject *seq;
    PyObject *item;

    if (!PyArg_ParseTuple(args, "O", &seq))
        return NULL;

    seq = PySequence_Fast(seq, "Argument must be iterable");
    if (!seq)
    {
        PyErr_SetString(PyExc_TypeError, "Memory allocation error");
        return NULL;
    }
    
    int n = PySequence_Fast_GET_SIZE(seq);

    int *arr = malloc(n * sizeof(int));

    if (arr == NULL)
    {
        PyErr_SetString(PyExc_TypeError, "Memory allocation error");
        Py_DecRef(seq);
        return NULL;
    }

    // Copying python list in array
    for (int i = 0; i < n; i++)
    {
        item = PySequence_Fast_GET_ITEM(seq, i);
        
        if (item == NULL)
        {
            PyErr_SetString(PyExc_TypeError, "Memory allocation error");
            Py_DecRef(seq);
            free(arr);
            return NULL;
        }

        if (PyLong_Check(item) == -1)
        {
            PyErr_SetString(PyExc_TypeError, "Bad arguments");
            Py_DecRef(seq);
            free(arr);
            return NULL;
        }


        arr[i] = PyLong_AsLong(item);
    }

    
    int needed_len = arr_nonsqr(arr, n, NULL, 0);

    if (needed_len < 0)
    {
        Py_DecRef(seq);
        free(arr);
        PyErr_SetString(PyExc_TypeError, "Read array error");
        return NULL;
    }

    int *new = malloc(needed_len * sizeof(int));

    if (new == NULL)
    {
        PyErr_SetString(PyExc_TypeError, "Memory allocation error");
        Py_DecRef(seq);
        free(arr);
        return NULL;
    }

    arr_nonsqr(arr, n, new, needed_len);

    PyObject *new_list = int_to_pylist(new, needed_len);

    free(new);
    Py_DecRef(seq);
    free(arr);

    return new_list;
}


static PyMethodDef libarr_wrapper[] =
{
    { "left_shift", py_arr_lshift, METH_VARARGS, "Performs left shift of list by k elems" },
    { "nonsqr", py_arr_nonsqr, METH_VARARGS, "Returns list of non-full sqr elems of given list" },
    { NULL, NULL, 0, NULL}
};

static struct PyModuleDef libarr_module = 
{
    PyModuleDef_HEAD_INIT,
    "arraylib",
    "Python wrap around C array library",
    -1,
    libarr_wrapper
};

PyMODINIT_FUNC PyInit_arraylib(void)
{
    return PyModule_Create(&libarr_module);
}
