#include <vector>
#include <cstddef>

template <typename A>
class Container
{
public:
    struct Tie
    {
        int m, n;
        A a;
        Tie(int _m, int _n, A _a) : m(_m), n(_n), a(_a) {}
    };
    std::vector<Tie> v;

    Container() {}

    void insert(int x, int y, A i)
    {
        v.push_back(Tie(x, y, i));
    }

    A *find(int x, int y)
    {
        for (Tie &tie : v)
        {
            if (tie.m == x && tie.n == y)
                return &(tie.a);
        }
        return NULL;
    }
};