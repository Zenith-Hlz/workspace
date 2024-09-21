#include <iostream>
#include "test.h"

struct PyObject
{
    char c;
    int i;
    double d;
    Test *t;
    bool own;
    PyObject() : i(0), d(0), c(0), own(false), t(nullptr) {}
    PyObject &operator=(char _c)
    {
        c = _c;
        std::cout << "PyObject got a value" << std::endl;
        if (own)
            delete t;
        return *this;
    }
    PyObject &operator=(int _i)
    {
        i = _i;
        std::cout << "PyObject got a value" << std::endl;
        if (own)
            delete t;
        return *this;
    }
    PyObject &operator=(double _d)
    {
        d = _d;
        std::cout << "PyObject got a value" << std::endl;
        if (own)
            delete t;
        return *this;
    }
    PyObject &operator=(Test &_t)
    {
        t = &_t;
        std::cout << "PyObject got a value\nBorrowing" << std::endl;
        return *this;
    }
    PyObject &operator=(Test &&_t)
    {
        std::cout << "PyObject got a value" << std::endl;
        t = new Test(std::move(_t));
        own = true;
        std::cout << "Owning" << std::endl;
        return *this;
    }
    PyObject &operator=(PyObject *_p)
    {
        std::cout << "PyObject got a value\nBorrowing" << std::endl;
        if (_p->own)
        {
            _p->own = false;
            own = true;
        }
        c = _p->c;
        i = _p->i;
        d = _p->d;
        t = _p->t;
        return *this;
    }
    PyObject &operator=(PyObject _p)
    {
        std::cout << "PyObject got a value\nBorrowing" << std::endl;
        if (_p.own)
        {
            _p.own = false;
            own = true;
        }
        c = _p.c;
        i = _p.i;
        d = _p.d;
        t = _p.t;
        return *this;
    }

    operator char() const { return c; }
    operator int() const { return i; }
    operator double() const { return d; }
    operator Test &() const { return *t; }
};