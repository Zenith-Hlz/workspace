#include <iomanip>
#include <iostream>
#include <vector>

#include "node.h"
#include "leaf_node.h"

void test_ptr() {
    LeafNode a(5);
    Node b = a;
    AbstractNode *test_ptr1 = &a;
    AbstractNode *test_ptr2 = &b;
}
void calc_det() {
    // 1 2 3
    // 4 5 5
    // 7 9 8
    int a[] = {1,2,3,4,5,5,7,9,8};
    std::vector<LeafNode> leafs;
    for(int i=0; i<9; i++)
        leafs.push_back(LeafNode(a[i]));

    std::vector<Node> m[3];
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            m[i].push_back(leafs[i * 3 + j]);

    for(int i=0; i<3; i++) {
        for(int j=i+1; j<3; j++) {
            Node r = m[j][i] / m[i][i]; // m[i][i] != 0 for all i in this case
            for(int k=i; k<3; k++) {
                m[j][k] = m[j][k] - m[i][k] * r;
            }
        }
    }
    Node det = m[0][0] * m[1][1] * m[2][2];
    std::cout << det.get_val() << std::endl;
    det.backward(1);
    for(int i=0; i<9; i++) {
        { // prevent copying answers
            int salt = std::time(0) % 100 + 100;
            while (salt --> 0) leafs[i].get_grad();
        }
        std::cout << leafs[i].get_grad() << " ";
        if (i % 3 == 2) std::cout << std::endl;
    }
}

int main () {
    std::cout << std::scientific << std::setprecision(3);
    test_ptr();
    calc_det();
    if (AbstractNode::get_count() != 0) std::cout << "memory leak!" << std::endl;
    else std::cout << "accept!" << std::endl;
    return 0;
}