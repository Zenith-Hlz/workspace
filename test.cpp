#include <cstdio>
#include <cstdlib>
#include <cassert>
#define LL long long

const int MAX_SIZE = 2e5 + 5;

int numIntervals, numOperations, uniqueCount, rawBoundaries[MAX_SIZE << 1]; // numIntervals: number of intervals, numOperations: number of operations, uniqueCount: count of unique values, rawBoundaries: array to store interval boundaries

struct Operation
{
    char type[2];    // Operation type ('H' for modify, 'Q' for query)
    int left, right; // Interval boundaries
} operations[MAX_SIZE];

struct Interval
{
    int left, right; // Interval boundaries
    Interval() {}
    Interval(int l, int r) : left(l), right(r) {}
} intervals[MAX_SIZE << 2];

LL segmentTreeSum[MAX_SIZE << 4];                                                                 // Segment tree to store sums
int segmentTreeChildren[MAX_SIZE << 4][2], lazyAdd[MAX_SIZE << 4], intervalLength[MAX_SIZE << 4]; // Segment tree children, lazy propagation array, and interval lengths

// Update the current node based on its children
void pushup(int node)
{
    segmentTreeSum[node] = segmentTreeSum[node << 1] + segmentTreeSum[node << 1 | 1];
    intervalLength[node] = intervalLength[node << 1] + intervalLength[node << 1 | 1];
}

// Propagate lazy updates to the children
void pushdown(int node)
{
    if (lazyAdd[node])
    {
        lazyAdd[node << 1] += lazyAdd[node];
        lazyAdd[node << 1 | 1] += lazyAdd[node];
        segmentTreeSum[node << 1] += 1LL * lazyAdd[node] * intervalLength[node << 1];
        segmentTreeSum[node << 1 | 1] += 1LL * lazyAdd[node] * intervalLength[node << 1 | 1];
        lazyAdd[node] = 0;
    }
}

// Build the segment tree
void build(int node, int left, int right)
{
    segmentTreeChildren[node][0] = left, segmentTreeChildren[node][1] = right;
    if (left == right)
    {
        intervalLength[node] = intervals[left].right - intervals[left].left + 1;
        return;
    }
    int mid = left + right >> 1;
    build(node << 1, left, mid);
    build(node << 1 | 1, mid + 1, right);
    pushup(node);
}

// Modify the segment tree within a specified range
void modify(int node, int left, int right, int value)
{
    if (left <= segmentTreeChildren[node][0] && segmentTreeChildren[node][1] <= right)
    {
        lazyAdd[node] += value;
        segmentTreeSum[node] += 1LL * value * intervalLength[node];
        return;
    }
    pushdown(node);
    int mid = segmentTreeChildren[node][0] + segmentTreeChildren[node][1] >> 1;
    if (left <= mid)
        modify(node << 1, left, right, value);
    if (mid < right)
        modify(node << 1 | 1, left, right, value);
    pushup(node);
}

// Query the sum within a specified range
LL query(int node, int left, int right)
{
    if (left <= segmentTreeChildren[node][0] && segmentTreeChildren[node][1] <= right)
        return segmentTreeSum[node];
    pushdown(node);
    int mid = segmentTreeChildren[node][0] + segmentTreeChildren[node][1] >> 1;
    LL result = 0;
    if (left <= mid)
        result += query(node << 1, left, right);
    if (mid < right)
        result += query(node << 1 | 1, left, right);
    return result;
}

// Comparison function for qsort
int compare(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

// Remove duplicates from the raw array
void deduplicate()
{
    uniqueCount = 0;
    qsort(rawBoundaries, 2 * numOperations, sizeof(int), compare);
    for (int i = 0, j = 0; j < 2 * numOperations; i++)
    {
        while (rawBoundaries[j] == rawBoundaries[i])
            j++;
        rawBoundaries[i + 1] = rawBoundaries[j];
        uniqueCount++;
    }
}

// Binary search to find the rank of a value
int search(int left, int right, int value)
{
    // Answer interval is [left, right)
    while (left < right - 1)
    {
        int mid = left + right >> 1;
        if (intervals[mid].left <= value)
        {
            left = mid;
        }
        else
        {
            right = mid;
        }
    }
    return left;
}

// Get the rank of a value within the intervals
int getRank(int value)
{
    return search(1, numIntervals + 1, value);
}

int main()
{
    // Read the number of intervals and operations
    scanf("%d %d", &numIntervals, &numOperations);
    for (int i = 1; i <= numOperations; i++)
    {
        char type[2];
        // Read each operation and store the interval boundaries
        scanf("%s %d %d", operations[i].type, &operations[i].left, &operations[i].right);
        rawBoundaries[i - 1 << 1] = operations[i].left;
        rawBoundaries[i - 1 << 1 | 1] = operations[i].right;
    }

    // Remove duplicates from the raw array
    deduplicate();

    // Construct the intervals
    numIntervals = 0;
    for (int i = 0; i < uniqueCount; i++)
    {
        intervals[++numIntervals] = Interval(rawBoundaries[i], rawBoundaries[i]);
        if (i < uniqueCount - 1 && rawBoundaries[i + 1] - rawBoundaries[i] > 1)
            intervals[++numIntervals] = Interval(rawBoundaries[i] + 1, rawBoundaries[i + 1] - 1);
    }

    // Build the segment tree
    build(1, 1, numIntervals);

    // Process each operation
    for (int i = 1; i <= numOperations; i++)
    {
        int left = getRank(operations[i].left);
        int right = getRank(operations[i].right);

        if (operations[i].type[0] == 'H')
            modify(1, left, right, 1); // Modify operation
        else if (operations[i].type[0] == 'Q')
            printf("%lld\n", query(1, left, right)); // Query operation
    }

    return 0;
}