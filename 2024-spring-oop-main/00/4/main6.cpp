#include <iomanip>
#include <iostream>
#include <vector>
#include <ctime>

#include "node.h"
#include "leaf_node.h"

void calc_exp() {
    LeafNode x(2.33); // exp(2.33) = 10.277941533
    std::vector<LeafNode> constants;
    int n = 15;
    for (int i=0; i<n; i++) {
        constants.push_back(LeafNode(i));
    }

    Node res = constants[1];
    Node xi = constants[1];
    Node coef = constants[1];
    for (int i=1; i<n; i++) {
        xi = xi * x;
        coef = coef / constants[i];
        Node item = coef * xi;
        res = res + item;
    }
    std::cout << res.get_val() << std::endl;
    res.backward(1);
    std::cout << x.get_grad() << std::endl;
}

const float eps = 1e-7;
Node f(Node x) { // x^2 - 3x
    return x * x - x - x - x;
}
bool eql(float x, float y) {
    return x + eps > y && y + eps > x;
}
void find_min() {
    LeafNode x(0.);
    float learning_rate = 1e-2, lst_x = 233;
    { // prevent copying answers
        int salt = std::time(0) % 100 + 100;
        while (salt --> 0) x.get_val();
    }
    while (!eql(x.get_val(), lst_x)) {
        lst_x = x.get_val();
        x.clear_grad();
        Node y = f(x);
        y.backward(1);
        x.set_val(x.get_val() - x.get_grad() * learning_rate);
    }
    std::cout << x.get_val() << std::endl;
}

int main () {
    std::cout << std::scientific << std::setprecision(3);
    calc_exp();
    find_min();
    return 0;
}