#include <stdio.h>
#include <algorithm>

#define MAX_LENGTH 64

int n = 0, total_length = 0, possible_length = 0, sticks[MAX_LENGTH], visited[MAX_LENGTH];

int compare(const int &a, const int &b)
{
    return a > b;
}

bool dfs(int count, int position, int sum)
{
    if (count == n)
        return true;

    for (int i = position; i < n; i++)
    {
        if (visited[i])
            continue;

        if (sum + sticks[i] < possible_length)
        {
            visited[i] = 1;
            if (dfs(count + 1, i + 1, sum + sticks[i]))
                return true;
            visited[i] = 0;
            
            while (sticks[i] == sticks[i + 1] && i + 1 < n)
                i++;
        }

        else if (sum + sticks[i] == possible_length)
        {
            visited[i] = 1;
            if (dfs(count + 1, 0, 0))
                return true;
            visited[i] = 0;
            return false;
        }

        if (sum == 0)
        {
            return false;
        }
    }

    return false;
}

int main()
{

    while (true)
    {
        scanf("%d", &n);
        if (n == 0)
            break;

        total_length = 0;

        for (int i = 0; i < n; i++)
        {
            scanf("%d", &sticks[i]);
            total_length += sticks[i];
            visited[i] = 0;
        }

        std::sort(sticks, sticks + n, compare);

        for (int i = n; i > 0; --i)
        {
            if (total_length % i == 0 && (total_length / i) >= sticks[0])
            {
                possible_length = total_length / i;
                if (dfs(0, 0, 0))
                {
                    printf("%d\n", possible_length);
                    break;
                }
            }
        }
    }

    return 0;
}