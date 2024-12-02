#include <cstdio>
#include <cstdlib>

const int MAXN = 200000;

struct Operation
{
    char operation[2]; // 'H' for modify, 'Q' for query
    int s, t;          // Interval boundaries
} operations[MAXN];

struct Interval
{
    int left, right; // Interval boundaries
    Interval() {}
    Interval(int l, int r) : left(l), right(r) {}
} intervals[MAXN << 2];

struct Node
{
    int l, r;      // The range [l, r] represented by this node
    long long sum; // Sum of flip counts in this range
    int lazy;      // Lazy propagation marker
    int len;       // Length of the range
    Node *left, *right;

    Node(int l, int r) : l(l), r(r), sum(0), lazy(0), left(nullptr), right(nullptr) {}
};

class SegmentTree
{
private:
    Node *root;

    // Propagate lazy value to children
    void pushDown(Node *node)
    {
        if (node->lazy)
        {
            // Apply lazy value to children
            if (node->left)
            {
                node->left->lazy += node->lazy;
                node->left->sum += 1LL * node->left->len * node->lazy;
            }

            if (node->right)
            {
                node->right->lazy += node->lazy;
                node->right->sum += 1LL * node->right->len * node->lazy;
            }

            // Clear lazy value for the current node
            node->lazy = 0;
        }
    }

    void build(Node *node, int left, int right)
    {
        node->l = left;
        node->r = right;
        if (left == right)
        {
            node->len = intervals[left].right - intervals[left].left + 1;
            return;
        }
        int mid = (left + right) >> 1;
        build(node->left = new Node(0, 0), left, mid);
        build(node->right = new Node(0, 0), mid + 1, right);

        node->len = (node->left ? node->left->len : 0) + (node->right ? node->right->len : 0);
    }

    // Update the range [ul, ur] by adding 1
    void update(Node *node, int ul, int ur)
    {
        if (ul <= node->l && node->r <= ur)
        {
            node->sum += 1LL * node->len;
            node->lazy++;
            return;
        }

        pushDown(node);

        int mid = (node->l + node->r) / 2;
        if (ul <= mid)
        {
            if (!node->left)
                node->left = new Node(node->l, mid);
            update(node->left, ul, ur);
        }
        if (ur > mid)
        {
            if (!node->right)
                node->right = new Node(mid + 1, node->r);
            update(node->right, ul, ur);
        }

        // Update current node's sum
        node->sum = (node->left ? node->left->sum : 0) + (node->right ? node->right->sum : 0);
    }

    // Query the sum in the range [ql, qr]
    long long query(Node *node, int ql, int qr)
    {
        if (!node)
            return 0;
        if (ql <= node->l && node->r <= qr)
            return node->sum;

        pushDown(node);

        int mid = (node->l + node->r) / 2;
        long long res = 0;
        if (ql <= mid && node->left)
            res += query(node->left, ql, qr);
        if (qr > mid && node->right)
            res += query(node->right, ql, qr);

        return res;
    }

public:
    SegmentTree(int left, int right)
    {
        root = new Node(left, right);
        build(root, left, right);
    }

    void update(int ul, int ur)
    {
        update(root, ul, ur);
    }

    long long query(int ql, int qr)
    {
        return query(root, ql, qr);
    }
};

int compare(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    int boundaries[MAXN << 1]; // Store the interval boundaries
    int totalBoundaries = 0;

    // Read operations and boundaries
    for (int i = 0; i < m; ++i)
    {
        scanf(" %c %d %d", operations[i].operation, &operations[i].s, &operations[i].t);
        boundaries[totalBoundaries++] = operations[i].s;
        boundaries[totalBoundaries++] = operations[i].t;
    }

    // Sort and deduplicate boundaries
    qsort(boundaries, totalBoundaries, sizeof(int), compare);
    int uniqueCount = 1; // At least one unique boundary
    for (int i = 1; i < totalBoundaries; ++i)
    {
        if (boundaries[i] != boundaries[uniqueCount - 1])
        {
            boundaries[uniqueCount++] = boundaries[i];
        }
    }

    // Construct the intervals
    int numIntervals = 0;
    for (int i = 0; i < uniqueCount; i++)
    {
        intervals[++numIntervals] = Interval(boundaries[i], boundaries[i]);
        if (i < uniqueCount - 1 && boundaries[i + 1] - boundaries[i] > 1)
            intervals[++numIntervals] = Interval(boundaries[i] + 1, boundaries[i + 1] - 1);
    }

    // Map boundaries to discrete indices
    auto getRank = [&](int value)
    {
        int left = 1, right = numIntervals + 1;
        while (left < right - 1)
        {
            int mid = (left + right) >> 1;
            if (intervals[mid].left <= value)
                left = mid;
            else
                right = mid;
        }
        return left;
    };

    SegmentTree segTree(1, numIntervals);

    // Process operations
    for (int i = 0; i < m; ++i)
    {
        int s = getRank(operations[i].s);
        int t = getRank(operations[i].t);

        if (operations[i].operation[0] == 'H')
        {
            segTree.update(s, t); // Flip operation
        }
        else if (operations[i].operation[0] == 'Q')
        {
            printf("%lld\n", segTree.query(s, t)); // Query operation
        }
    }

    return 0;
}
