#pragma once
#include <iostream>
using namespace std;

struct Counter
{
public:
    int s, w;
    Counter(int _s = 0, int _w = 0) : s(_s), w(_w) {}
};

template <class T>
class MyWeakPtr;

template <class T>
class MySharedPtr
{
private:
    T *data;
    Counter *refCount;
    void release()
    {
        if (refCount)
        {
            refCount->s--;
            if (refCount->s == 0)
            {
                cout << "data released.\n";
                delete data;
                if (refCount->w == 0)
                {
                    delete refCount;
                }
            }
        }
    }

public:
    MySharedPtr() : data(nullptr), refCount(nullptr)
    {
        cout << "my_sptr constructed.\n";
    }
    MySharedPtr(T *p) : data(p), refCount(new Counter(1, 0))
    {
        cout << "my_sptr constructed.\n";
    }
    MySharedPtr(MySharedPtr<T> &&sp) : data(sp.data), refCount(sp.refCount)
    {
        sp.data = nullptr;
        sp.refCount = nullptr;
        cout << "my_sptr constructed.\n";
    }
    MySharedPtr(const MyWeakPtr<T> &wp) : data(wp.expired() ? nullptr : wp.data), refCount(wp.expired() ? nullptr : wp.refCount)
    {
        if (refCount)
        {
            refCount->s++;
        }
        cout << "my_sptr constructed." << endl;
    }
    MySharedPtr(const MySharedPtr<T> &sp) : data(sp.data), refCount(sp.refCount)
    {
        if (refCount)
        {
            refCount->s++;
        }
        cout << "my_sptr constructed.\n";
    }
    ~MySharedPtr()
    {
        cout << "my_sptr destructed.\n";
        release();
    }
    MySharedPtr<T> &operator=(MySharedPtr<T> &&sp)
    {
        cout << "my_sptr updated.\n";
        if (this != &sp)
        {
            release();
            data = sp.data;
            refCount = sp.refCount;
            sp.data = nullptr;
            sp.refCount = nullptr;
        }

        return *this;
    }
    MySharedPtr<T> &operator=(const MySharedPtr<T> &sp)
    {
        cout << "my_sptr updated.\n";
        if (this != &sp)
        {
            release();
            data = sp.data;
            refCount = sp.refCount;
            if (refCount)
            {
                refCount->s++;
            }
        }

        return *this;
    }

    int use_count() const
    {
        return refCount ? refCount->s : 0;
    }
    T &operator*()
    {
        return *data;
    }
    T *operator->()
    {
        return data;
    }
    operator bool() const
    {
        return data != nullptr;
    }
    friend class MyWeakPtr<T>;
};

template <class T>
class MyWeakPtr
{
private:
    Counter *refCount;
    T *data;
    void release()
    {
        if (refCount)
        {
            refCount->w--;
            if (refCount->s == 0 && refCount->w == 0)
            {
                delete refCount;
            }
        }
    }

public:
    MyWeakPtr() : data(nullptr), refCount(nullptr)
    {
        cout << "my_wptr constructed.\n";
    }
    MyWeakPtr(MySharedPtr<T> &sp) : data(sp.data), refCount(sp.refCount)
    {
        if (refCount)
        {
            refCount->w++;
        }
        cout << "my_wptr constructed.\n";
    }
    MyWeakPtr(const MyWeakPtr &wp) : data(wp.data), refCount(wp.refCount)
    {
        if (refCount)
        {
            refCount->w++;
        }
        cout << "my_wptr constructed.\n";
    }
    MyWeakPtr(MyWeakPtr &&wp) : data(wp.data), refCount(wp.refCount)
    {
        wp.data = nullptr;
        wp.refCount = nullptr;
        cout << "my_wptr constructed.\n";
    }
    ~MyWeakPtr()
    {
        cout << "my_wptr destructed.\n";
        release();
    }

    MyWeakPtr<T> &operator=(const MyWeakPtr<T> &wp)
    {
        cout << "my_wptr updated.\n";
        if (this != &wp)
        {
            release();
            data = wp.data;
            refCount = wp.refCount;
            if (refCount)
            {
                refCount->w++;
            }
        }
        return *this;
    }

    MyWeakPtr<T> &operator=(const MySharedPtr<T> &sp)
    {
        cout << "my_wptr updated.\n";
        release();
        data = sp.data;
        refCount = sp.refCount;
        if (refCount)
        {
            refCount->w++;
        }

        return *this;
    }

    MyWeakPtr<T> &operator=(MyWeakPtr<T> &&wp)
    {
        cout << "my_wptr updated.\n";
        if (this != &wp)
        {
            release();
            data = wp.data;
            refCount = wp.refCount;
            wp.data = nullptr;
            wp.refCount = nullptr;
        }

        return *this;
    }

    bool expired() const
    {
        return !refCount || refCount->s == 0;
    }
    MySharedPtr<T> lock() const
    {
        return expired() ? MySharedPtr<T>() : MySharedPtr<T>(*this);
    }

    int use_count() const
    {
        return refCount ? refCount->s : 0;
    }

    friend class MySharedPtr<T>;
};
