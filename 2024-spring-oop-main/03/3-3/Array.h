#pragma once
#include "Node.h"

struct Array
{
private:
    int len;
    Node *elements;

public:
    Array(int l) : len(l), elements(new Node[l]) {}

    // Copy constructor
    Array(const Array &other) : len(other.len), elements(new Node[other.len])
    {
        for (int i = 0; i < len; ++i)
        {
            elements[i] = other.elements[i];
        }
    }

    // Destructor
    ~Array()
    {
        delete[] elements;
    }

    // Operator overloading for accessing elements
    Node &operator[](int idx)
    {
        return elements[idx];
    }

    // Copy assignment operator
    Array &operator=(const Array &other)
    {
        if (this != &other)
        {
            delete[] elements;
            len = other.len;
            elements = new Node[len];
            for (int i = 0; i < len; ++i)
            {
                elements[i] = other.elements[i];
            }
        }
        return *this;
    }

    // Move assignment operator
    Array &operator=(Array &&other)
    {
        if (this != &other)
        {
            delete[] elements;
            len = other.len;
            elements = other.elements;
            other.elements = nullptr;
            other.len = 0;
        }
        return *this;
    }
};
