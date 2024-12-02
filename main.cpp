#include <cstdio>

const int MAXN = 200000;
struct SegmentTree
{
    long long sum[MAXN * 4];
    long long lazy[MAXN * 4];

    void build(int node, int start, int end)
    {
        sum[node] = 0;
        lazy[node] = 0;
        if (start == end)
        {
            return;
        }
        int mid = (start + end) / 2;
        build(node * 2, start, mid);
        build(node * 2 + 1, mid + 1, end);
    }

    void propagate(int node, int start, int end)
    {
        if (lazy[node] != 0)
        {
            sum[node] += lazy[node] * (end - start + 1);
            if (start != end)
            {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    void update(int node, int start, int end, int l, int r, int value)
    {
        propagate(node, start, end);
        if (r < start || l > end)
        {
            return;
        }
        if (l <= start && end <= r)
        {
            lazy[node] += value;
            propagate(node, start, end);
            return;
        }
        int mid = (start + end) / 2;
        update(node * 2, start, mid, l, r, value);
        update(node * 2 + 1, mid + 1, end, l, r, value);
        sum[node] = sum[node * 2] + sum[node * 2 + 1];
    }

    long long query(int node, int start, int end, int l, int r)
    {
        propagate(node, start, end);
        if (r < start || l > end)
        {
            return 0;
        }
        if (l <= start && end <= r)
        {
            return sum[node];
        }
        int mid = (start + end) / 2;
        return query(node * 2, start, mid, l, r) +
               query(node * 2 + 1, mid + 1, end, l, r);
    }
};

SegmentTree segTree;

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    segTree.build(1, 1, n);

    for (int i = 0; i < m; ++i)
    {
        char operation;
        int s, t;
        scanf(" %c %d %d", &operation, &s, &t);
        if (operation == 'H')
        {
            segTree.update(1, 1, n, s, t, 1);
        }
        if (operation == 'Q')
        {
            printf("%lld\n", segTree.query(1, 1, n, s, t));
        }
    }

    return 0;
}
