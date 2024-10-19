#include <cstdio>

void swapPointers(const char *&a, const char *&b)
{
    const char *temp = a;
    a = b;
    b = temp;
}

void swapIntegers(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

inline int customMax(int a, int b)
{
    return (a > b) ? a : b;
}

inline int customMin(int a, int b)
{
    return (a < b) ? a : b;
}

int LCS(const char *A, int N, const char *B, int M, int K)
{
    if (N < M)
    {
        swapPointers(A, B);
        swapIntegers(N, M);
    }

    int range = 2 * K + 1;
    int *dp_prev = new int[range]();
    int *dp_curr = new int[range]();

    for (int i = 1; i <= N; ++i)
    {
        for (int j = customMax(1, i - K); j <= customMin(M, i + K); ++j)
        {
            if (A[i - 1] == B[j - 1])
            {
                dp_curr[j] = dp_prev[j - 1] + 1;
            }
            else
            {
                dp_curr[j] = (dp_curr[j - 1] > dp_prev[j]) ? dp_curr[j - 1] : dp_prev[j];
            }
        }
        int *temp = dp_prev;
        dp_prev = dp_curr;
        dp_curr = temp;
    }

    int lcs_length = dp_prev[M];
    delete[] dp_prev;
    delete[] dp_curr;

    return lcs_length;
}

int main()
{
    int N, M, K;
    scanf("%d %d %d", &N, &M, &K);

    char *A = new char[N + 1];
    char *B = new char[M + 1];

    scanf("%s", A);
    scanf("%s", B);

    // Calculate LCS only within the range |i-j| <= K
    int lcs_length = LCS(A, N, B, M, K);
    int transformation_cost = N + M - 2 * lcs_length;

    if (transformation_cost > K)
    {
        printf("-1\n");
    }
    else
    {
        printf("%d\n", transformation_cost);
    }

    delete[] A;
    delete[] B;

    return 0;
}