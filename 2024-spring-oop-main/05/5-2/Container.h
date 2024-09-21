#ifndef CONTAINER_H
#define CONTAINER_H
#include "BasicContainer.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

using std::map;
using std::vector;

template <class A>
struct Point
{
    Pos pos;
    A value;
    Point(Pos p, A v) : pos(p), value(v) {}
    bool operator<(const Point &other) const
    {
        return pos < other.pos;
    }
};

template <class A, class C>
class Container : public BasicContainer<A>
{
public:
    void insert(const Pos &p, const A &v) {};
    A *find(Pos p) { return NULL; };
};

template <class A>
class Container<A, vector<A>> : public BasicContainer<A>
{
    vector<Point<A>> base;
    bool is_sorted = false;

public:
    void insert(const Pos &p, const A &v)
    {
        base.push_back(Point<A>(p, v));
        is_sorted = false;
    }

    A *find(Pos p)
    {
        if (!is_sorted)
        {
            std::sort(base.begin(), base.end());
            is_sorted = true;
        }
        auto it = std::lower_bound(base.begin(), base.end(), Point<A>(p, A()));
        if (it != base.end() && it->pos == p)
        {
            return &it->value;
        }
        return NULL;
    }
};

template <class A>
class Container<A, map<Pos, A>> : public BasicContainer<A>
{
    map<Pos, A> base;

public:
    void insert(const Pos &p, const A &v)
    {
        base[p] = v;
    }

    A *find(Pos p)
    {
        auto it = base.find(p);
        if (it != base.end())
        {
            return &it->second;
        }
        return nullptr;
    }
};

#endif
