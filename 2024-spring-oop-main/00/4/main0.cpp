#include <iomanip>
#include <iostream>

#include "node.h"
#include "leaf_node.h"

void test1() {
    LeafNode a(1.234), b(5.678), c(9.012);
    Node d = a + b;
    Node e = a - c;
    Node f = d + b;
    Node g = b - e;
    Node h = f + g;
    std::cout << h.get_val() << std::endl;
}

void test2() {
    LeafNode a(1.234), b(5.678), c(9.012);
    Node d = a - b + c;
    d = d + d + a + a + b - c;
    d = d - c;
    std::cout << d.get_val() << std::endl;
}

int main () {
    std::cout << std::scientific << std::setprecision(3);
    test1();
    test2();
    return 0;
}