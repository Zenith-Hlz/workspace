#include <cstdio>
#include <cstdlib>

const int MAXN = 200000;

struct Operation
{
    char operation; // 'H' for modify, 'Q' for query
    int s, t;       // Interval boundaries
} operations[MAXN];

int boundaries[MAXN << 1];    // Store the interval boundaries
int intervalLeft[MAXN << 2];  // Interval left boundaries
int intervalRight[MAXN << 2]; // Interval right boundaries

// Node structure for the segment tree
struct Node
{
    int start, end; // The range [start, end] represented by this node
    int lazy;       // Lazy value for horizontal flip
    int length;     // Length of the range
    long long sum;  // Sum of flip counts in this range
    Node *leftChild, *rightChild;

    Node(int start, int end) : start(start), end(end), lazy(0), length(0), sum(0), leftChild(nullptr), rightChild(nullptr) {}
};

class SegmentTree
{
private:
    Node *root;

    // Helper functions for segment tree push down
    void applyLazyUpdate(Node *child, int lazyValue)
    {
        if (child)
        {
            // Apply the lazy value to the child node
            child->lazy += lazyValue;
            child->sum += 1LL * child->length * lazyValue;
        }
    }

    // Propagate lazy value to children
    void pushDown(Node *node)
    {
        if (node->lazy)
        {
            // Apply lazy value to children
            applyLazyUpdate(node->leftChild, node->lazy);
            applyLazyUpdate(node->rightChild, node->lazy);

            // Clear lazy value for the current node
            node->lazy = 0;
        }
    }

    // Helper functions for segment tree build
    void initializeChild(Node *&child, int rangeStart, int rangeEnd)
    {
        child = new Node(0, 0);
        build(child, rangeStart, rangeEnd); // Recursively build the child node
    }

    // Build the segment tree
    void build(Node *node, int rangeStart, int rangeEnd)
    {
        // Initialize range for the current node
        node->start = rangeStart;
        node->end = rangeEnd;

        // Base case: leaf node
        if (rangeStart == rangeEnd)
        {
            node->length = intervalRight[rangeStart] - intervalLeft[rangeStart] + 1;
            return;
        }

        // Calculate the midpoint of the current range
        int midpoint = (rangeStart + rangeEnd) / 2;

        // Recursively build left and right children
        initializeChild(node->leftChild, rangeStart, midpoint);
        initializeChild(node->rightChild, midpoint + 1, rangeEnd);

        // Update the range length of the current node
        node->length = node->leftChild->length + node->rightChild->length;
    }

    // Horizontal flip the range [updateStart, updateEnd]
    void flip(Node *node, int updateStart, int updateEnd)
    {
        // If the current range is completely within [updateStart, updateEnd]
        if (updateStart <= node->start && node->end <= updateEnd)
        {
            node->sum += 1LL * node->length;
            node->lazy++;
            return;
        }

        // If the current range is completely outside [updateStart, updateEnd], skip it
        if (node->end < updateStart || node->start > updateEnd)
            return;

        // Push lazy updates to children
        pushDown(node);

        // Recursive updates on children
        int midpoint = (node->start + node->end) / 2;

        if (updateStart <= midpoint)
            flip(node->leftChild, updateStart, updateEnd);
        if (updateEnd > midpoint)
            flip(node->rightChild, updateStart, updateEnd);

        // Recalculate the sum after updates
        node->sum = (node->leftChild ? node->leftChild->sum : 0) + (node->rightChild ? node->rightChild->sum : 0);
    }

    // Query the sum in the range [queryStart, queryEnd]
    long long query(Node *node, int queryStart, int queryEnd)
    {
        if (!node)
            return 0; // If the node is null, return 0

        // If the current range is completely within [queryStart, queryEnd]
        if (queryStart <= node->start && node->end <= queryEnd)
            return node->sum;

        // If the current range is completely outside [queryStart, queryEnd], return 0
        if (node->end < queryStart || node->start > queryEnd)
            return 0;

        // Push lazy updates to children
        pushDown(node);

        // Recursive query on children
        int midpoint = (node->start + node->end) / 2;
        long long leftSum = 0, rightSum = 0;
        if (queryStart <= midpoint)
            leftSum = query(node->leftChild, queryStart, queryEnd);
        if (queryEnd > midpoint)
            rightSum = query(node->rightChild, queryStart, queryEnd);

        // Return the combined sum
        return leftSum + rightSum;
    }

public:
    // Constructor for the segment tree
    SegmentTree(int rangeStart, int rangeEnd)
    {
        root = new Node(rangeStart, rangeEnd);
        build(root, rangeStart, rangeEnd);
    }

    // Horizontal flip the range [updateStart, updateEnd]
    void flip(int updateStart, int updateEnd)
    {
        flip(root, updateStart, updateEnd);
    }

    // Query the sum in the range [queryStart, queryEnd]
    long long query(int queryStart, int queryEnd)
    {
        return query(root, queryStart, queryEnd);
    }
};

// Helper function to compare two integers for qsort
int compare(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

// Parse input and read operations
void readInput(int &numIntervals, int &numOperations)
{
    scanf("%d %d", &numIntervals, &numOperations);

    int totalBoundaries = 0;
    for (int i = 0; i < numOperations; ++i)
    {
        scanf(" %c %d %d", &operations[i].operation, &operations[i].s, &operations[i].t);
        boundaries[totalBoundaries++] = operations[i].s;
        boundaries[totalBoundaries++] = operations[i].t;
    }
}

// Deduplicate and sort boundaries
int deduplicateBoundaries(int totalBoundaries)
{
    qsort(boundaries, totalBoundaries, sizeof(int), compare);

    int uniqueCount = 1;
    for (int i = 1; i < totalBoundaries; ++i)
    {
        if (boundaries[i] != boundaries[uniqueCount - 1])
            boundaries[uniqueCount++] = boundaries[i];
    }
    return uniqueCount;
}

// Construct intervals from deduplicated boundaries
int constructIntervals(int uniqueCount)
{
    int numIntervals = 0;
    for (int i = 0; i < uniqueCount; ++i)
    {
        intervalLeft[++numIntervals] = boundaries[i];
        intervalRight[numIntervals] = boundaries[i];

        if (i < uniqueCount - 1 && boundaries[i + 1] - boundaries[i] > 1)
        {
            intervalLeft[++numIntervals] = boundaries[i] + 1;
            intervalRight[numIntervals] = boundaries[i + 1] - 1;
        }
    }
    return numIntervals;
}

// Map a value to its discrete index
int getRank(int value, int numIntervals)
{
    int left = 1, right = numIntervals + 1;
    while (left < right - 1)
    {
        int mid = (left + right) / 2;
        if (intervalLeft[mid] <= value)
            left = mid;
        else
            right = mid;
    }
    return left;
}

// Process operations using the segment tree
void processOperations(SegmentTree &segTree, int numOperations, int numIntervals)
{
    for (int i = 0; i < numOperations; ++i)
    {
        int startIndex = getRank(operations[i].s, numIntervals);
        int endIndex = getRank(operations[i].t, numIntervals);

        if (operations[i].operation == 'H')
            segTree.flip(startIndex, endIndex); // Flip operation
        else if (operations[i].operation == 'Q')
            printf("%lld\n", segTree.query(startIndex, endIndex)); // Query operation
    }
}

int main()
{
    int n, m;

    readInput(n, m);

    int uniqueCount = deduplicateBoundaries(m * 2);
    n = constructIntervals(uniqueCount);

    SegmentTree segTree(1, n);

    processOperations(segTree, m, n);

    return 0;
}