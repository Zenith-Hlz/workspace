#include <iostream>
#include <bitset>

int main()
{
    int a = -214748364;
    int b = a | (-a);
    std::cout << (b >> 31) << std::endl;
    std::cout << std::bitset<32>(a) << std::endl;
    std::cout << std::bitset<32>(-a) << std::endl;
    std::cout << std::bitset<32>(b) << std::endl;
    return 0;
}