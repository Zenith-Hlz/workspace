#include <cstdio>

struct TreeNode
{
    int size;      // Size of subtree rooted at this node
    int height;    // Height of subtree rooted at this node
    TreeNode *fir; // Pointer to the first child node
    TreeNode *sib; // Pointer to the next sibling node
    TreeNode *par; // Pointer to the parent node

    // Constructor to initialize each TreeNode with default values
    TreeNode() : size(1), height(0), fir(nullptr), sib(nullptr), par(nullptr) {}
};

const int MAXN = 1000009;
TreeNode nodes[MAXN];

// Function to calculate subtree size and height recursively for a given node
int composeSizeAndHeight(TreeNode *node)
{
    if (!node->fir) // If node has no children, it is a leaf
    {
        node->size = 1;
        node->height = 0;
        return node->height;
    }

    int newHeight = 0, newSize = 1;
    TreeNode *child = node->fir;
    while (child) // Traverse all children of the current node
    {
        int childHeight = composeSizeAndHeight(child);
        newSize += child->size;          // Accumulate size of each child subtree
        if (childHeight + 1 > newHeight) // Update height if needed
            newHeight = childHeight + 1;
        child = child->sib; // Move to the next sibling
    }

    node->size = newSize; // Update size and height of the current node
    node->height = newHeight;
    return node->height;
}

// Function to update the size and height of ancestors after a subtree move
void updateAncestors(TreeNode *node)
{
    while (node) // Traverse up from the given node to the root
    {
        int newHeight = 0, newSize = 1;
        if (node->fir)
        {
            TreeNode *child = node->fir;
            while (child)
            {
                newSize += child->size;
                if ((child->height + 1) > newHeight)
                    newHeight = child->height + 1;
                child = child->sib;
            }
        }
        // If both size and height match the expected values, no further updates needed
        if (node->size == newSize && node->height == newHeight)
            break;
        node->size = newSize;
        node->height = newHeight;
        node = node->par; // Move to the parent
    }
}

// Finds a node given a path of child indices
TreeNode *findNode(int pathLen, int *path)
{
    TreeNode *current = &nodes[1]; // Start from the root node
    for (int i = 0; i < pathLen; i++)
    {
        if (!(current->fir)) // If node has no children, path is invalid
            return current;
        TreeNode *child = current->fir;
        int rank = path[i];
        for (int j = 0; j < rank; j++)
        {
            if (!(child->sib)) // If there aren't enough siblings, return current node
                return current;
            child = child->sib;
        }
        current = child; // Move to the selected child
    }
    return current;
}

// Moves subtree rooted at `s` to be the k-th child of node `d`
void moveSubtree(int sLen, int *sPath, int dLen, int *dPath, int k)
{
    TreeNode *s = findNode(sLen, sPath);
    TreeNode *parent = s->par;

    // Detach `s` from its current position in the parent's child list
    if (parent->fir == s) // If `s` is the first child
    {
        parent->fir = s->sib;
    }
    else // Traverse to find `s` in siblings
    {
        TreeNode *child = parent->fir;
        while (child && child->sib != s)
        {
            child = child->sib;
        }
        if (child)
            child->sib = s->sib; // Detach `s`
    }
    s->sib = nullptr;

    TreeNode *d = findNode(dLen, dPath);
    s->par = d; // Set new parent

    // Insert `s` as the k-th child of `d`
    if (k == 0) // Insert as the first child
    {
        s->sib = d->fir;
        d->fir = s;
    }
    else
    {
        TreeNode *child = d->fir;
        for (int i = 1; i < k && child->sib; i++)
        {
            child = child->sib;
        }
        s->sib = child->sib;
        child->sib = s;
    }

    // Update sizes and heights of affected ancestors
    updateAncestors(d);
    updateAncestors(parent);
}

// Queries height of a node
int queryHeight(TreeNode *node)
{
    return node ? node->height : 0;
}

// Queries size of a node
int querySize(TreeNode *node)
{
    return node ? node->size : 0;
}

int main()
{
    int N, M;
    scanf("%d %d", &N, &M);

    // Build the tree from input
    for (int i = 1; i <= N; i++)
    {
        int childCount;
        scanf("%d", &childCount);
        if (childCount > 0)
        {
            int firstChild;
            scanf("%d", &firstChild);
            nodes[i].fir = &nodes[firstChild];
            nodes[firstChild].par = &nodes[i];
            TreeNode *current = nodes[i].fir;
            for (int j = 1; j < childCount; j++)
            {
                int child;
                scanf("%d", &child);
                current->sib = &nodes[child];
                nodes[child].par = &nodes[i];
                current = current->sib;
            }
        }
    }

    // Initialize sizes and heights for all nodes in the tree
    composeSizeAndHeight(&nodes[1]);

    // Process each operation
    for (int i = 0; i < M; i++)
    {
        int op;
        scanf("%d", &op);
        if (op == 0) // Move operation
        {
            int sLen, dLen, k;
            scanf("%d", &sLen);
            int sPath[sLen];
            for (int j = 0; j < sLen; ++j)
                scanf("%d", &sPath[j]);
            scanf("%d", &dLen);
            int dPath[dLen];
            for (int j = 0; j < dLen; ++j)
                scanf("%d", &dPath[j]);
            scanf("%d", &k);

            moveSubtree(sLen, sPath, dLen, dPath, k);
        }
        else // Query operation
        {
            int pathLen;
            scanf("%d", &pathLen);
            int path[pathLen];
            for (int j = 0; j < pathLen; ++j)
                scanf("%d", &path[j]);

            TreeNode *node = findNode(pathLen, path);
            printf("%d\n", (op == 1) ? queryHeight(node) : querySize(node));
        }
    }

    return 0;
}