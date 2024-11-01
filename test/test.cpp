#include <iostream>

int main()
{
    long long a = 4294967290;
    int b = 2147483647;
    int c = (a < b) ? a : b;
    std::cout << c << std::endl;
}