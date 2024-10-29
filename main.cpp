#include <cstdio>
#include <cstdlib>
#include <climits>

// Function to compare integers for qsort
int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

// Function to perform binary search for upper bound
int upper_bound(int *arr, int size, int value)
{
    int low = 0, high = size;
    while (low < high)
    {
        int mid = (low + high) / 2;
        if (arr[mid] <= value)
        {
            low = mid + 1;
        }
        else
        {
            high = mid;
        }
    }
    return low;
}

int main()
{
    int n;
    scanf("%d", &n);
    int *cases = new int[n];
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &cases[i]);
    }

    int *m = new int[n];
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &m[i]);
    }

    int *d = new int[n];
    int *queap = new int[n];
    int front = 0, back = 0;

    // Calculate d_i using a monotonic deque
    for (int i = 0; i < n; ++i)
    {
        if (front < back && queap[front] <= i - m[i])
        {
            ++front;
        }

        while (front < back && cases[queap[back - 1]] <= cases[i])
        {
            --back;
        }

        queap[back++] = i;
        d[i] = cases[queap[front]];
    }

    for (int i = 0; i < n; i++)
    {
        printf("%d\n", d[i]);
    }

    // Sort d to make threshold querying efficient
    qsort(d, n, sizeof(int), compare);

    int T;
    scanf("%d", &T);
    for (int t = 0; t < T; ++t)
    {
        int p, q;
        scanf("%d%d", &p, &q);

        // Use binary search to find the counts
        int lowRiskCount = upper_bound(d, n, p - 1) + 1;
        int mediumRiskCount = upper_bound(d, n, q - 1) + 1 - lowRiskCount;

        printf("%d %d\n", lowRiskCount, mediumRiskCount);
    }

    delete[] cases;
    delete[] m;
    delete[] d;
    delete[] queap;

    return 0;
}