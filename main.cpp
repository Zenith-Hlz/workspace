#include <iostream>

const int MAXN = 1000001;

struct Node
{
    int value;
    int dist;
    int size;
    Node *left;
    Node *right;

    Node(int value) : value(value), dist(0), size(1), left(nullptr), right(nullptr) {}
};

int n, m, k, q;
int parent[MAXN];
Node *nodes[MAXN];

int find(int x)
{
    return parent[x] == x ? x : parent[x] = find(parent[x]);
}

Node *merge(Node *a, Node *b)
{
    if (!a || !b)
        return a ? a : b;

    if (a->value > b->value)
        std::swap(a, b);
    a->right = merge(a->right, b);
    if (!a->left || a->left->dist < a->right->dist)
        std::swap(a->left, a->right);
    a->dist = a->right ? a->right->dist + 1 : 0;
    a->size = 1 + (a->left ? a->left->size : 0) + (a->right ? a->right->size : 0);

    while (a->size > k)
        a = merge(a->left, a->right);

    return a;
}

void join(int u, int v)
{
    int root_u = find(u), root_v = find(v);
    if (root_u == root_v)
        return;

    parent[root_v] = root_u;
    nodes[root_u] = merge(nodes[root_u], nodes[root_v]);
}

int query(int u)
{
    int root = find(u);

    return nodes[root]->size < k ? -1 : nodes[root]->value;
}

int main()
{
    scanf("%d %d %d %d", &n, &m, &k, &q);

    for (int i = 1; i <= n; i++)
    {
        int node;
        scanf("%d", &node);
        nodes[i] = new Node(node);
        parent[i] = i;
    }
    for (int i = 0; i < m; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        join(u, v);
    }
    for (int i = 0; i < q; i++)
    {
        int op, u, v;
        scanf("%d", &op);
        if (op == 1)
        {
            scanf("%d %d", &u, &v);
            join(u, v);
        }
        else
        {
            scanf("%d", &u);
            printf("%d\n", query(u));
        }
    }
}