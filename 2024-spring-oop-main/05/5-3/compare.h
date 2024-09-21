#pragma once

#include "abstract_compare.h"
#include "point.h"

class CompareIntDefault : public AbstractCompare<int>
{
public:
    bool compare(int a, int b) override
    {
        return a < b;
    }
};

class CompareIntSum : public AbstractCompare<int>
{
public:
    bool compare(int a, int b) override
    {
        auto digit_sum = [](int n)
        {
            int sum = 0;
            while (n)
            {
                sum += n % 10;
                n /= 10;
            }
            return sum;
        };
        int sum_a = digit_sum(a);
        int sum_b = digit_sum(b);
        if (sum_a != sum_b)
        {
            return sum_a < sum_b;
        }
        return a < b;
    }
};

bool operator<(const Point &a, const Point &b)
{
    if (a.x != b.x)
    {
        return a.x < b.x;
    }
    return a.y < b.y;
}

class ComparePointDefault : public AbstractCompare<Point>
{
public:
    bool compare(Point a, Point b) override
    {
        return a < b;
    }
};

class ComparePointDistance : public AbstractCompare<Point>
{
public:
    bool compare(Point a, Point b) override
    {
        auto pow_distance = [](Point p)
        {
            return p.x * p.x + p.y * p.y;
        };
        int dist_a = pow_distance(a);
        int dist_b = pow_distance(b);
        if (dist_a != dist_b)
        {
            return dist_a < dist_b;
        }
        return a < b;
    }
};

AbstractCompare<int> *get_compare_int(int type)
{
    if (type == 1)
    {
        return new CompareIntDefault();
    }
    else if (type == 2)
    {
        return new CompareIntSum();
    }
    return nullptr;
}
AbstractCompare<Point> *get_compare_point(int type)
{
    if (type == 3)
    {
        return new ComparePointDefault();
    }
    else if (type == 4)
    {
        return new ComparePointDistance();
    }
    return nullptr;
}
