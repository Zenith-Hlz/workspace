#include "leaf_node.h"

LeafNode::LeafNode(float _val) : val(_val), grad(0) {}

LeafNode::~LeafNode() {}

float LeafNode::get_val() {
    return val;
}

void LeafNode::set_val(float _val) {
    val = _val;
}

float LeafNode::get_grad() {
    return grad;
}

void LeafNode::backward(float _grad) {
    grad += _grad;
}

void LeafNode::clear_grad() {
    grad = 0;
}

LeafNode::operator Node() const {
    return Node(std::make_shared<LeafNode>(*this));
}
