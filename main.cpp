#include <stdio.h>

void f(int n)
{
    int s = 0, i = 0;
    while (s <= n)
    {
        ++i;
        s += i ^ 2;
        printf("*");
    }
}