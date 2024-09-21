#pragma once

#include "abstract_node.h"
#include <memory>
#include <iostream>

class Node : public AbstractNode {
    std::shared_ptr<AbstractNode> node;

public:
    Node(std::shared_ptr<AbstractNode> _node) : node(_node) {}
    Node() : node(nullptr) {}

    float get_val() override {
        return node->get_val();
    }

    void backward(float _grad) override {
        node->backward(_grad);
    }

    friend Node operator+(const Node &x, const Node &y);
    friend Node operator-(const Node &x, const Node &y);
    friend Node operator*(const Node &x, const Node &y);
    friend Node operator/(const Node &x, const Node &y);
};

Node operator+(const Node &x, const Node &y);
Node operator-(const Node &x, const Node &y);
Node operator*(const Node &x, const Node &y);
Node operator/(const Node &x, const Node &y);
