#pragma once
#include "abstract_node.h"
#include "node.h"

class LeafNode : public AbstractNode {
    float val, grad;

public:
    LeafNode(float _val);
    ~LeafNode();
    float get_val() override;
    void set_val(float _val);
    float get_grad();
    void backward(float _grad) override;
    void clear_grad();

    operator Node() const; // Implicit conversion operator
};
