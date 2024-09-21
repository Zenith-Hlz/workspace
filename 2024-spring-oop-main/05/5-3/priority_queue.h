#pragma once
#include "abstract_compare.h"
#include <vector>
#include <algorithm>

template <class T>
class PriorityQueue
{
private:
    std::vector<T> elements;
    AbstractCompare<T> *comparator;

public:
    PriorityQueue(AbstractCompare<T> *_cmp) : comparator(_cmp) {}
    ~PriorityQueue() {}
    bool empty()
    {
        return elements.empty();
    }
    int size()
    {
        return elements.size();
    }
    void push(T element)
    {
        elements.push_back(element);
        std::sort(elements.begin(), elements.end(), [&](T a, T b)
                  { return comparator->compare(a, b); });
    }
    void pop()
    {
        if (!elements.empty())
        {
            elements.erase(elements.begin());
        }
    }
    T top()
    {
        if (!elements.empty())
        {
            return elements.front();
        }
        throw std::runtime_error("PriorityQueue is empty");
    }
};