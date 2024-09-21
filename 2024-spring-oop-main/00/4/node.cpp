#include "node.h"
#include "leaf_node.h"
#include <iostream>

// Abstract operator base class for different operations
class AbstractOperator : public AbstractNode {
protected:
    Node a, b;

public:
    AbstractOperator(const Node &_a, const Node &_b) : a(_a), b(_b) {}
};

class AddOperator : public AbstractOperator {
public:
    using AbstractOperator::AbstractOperator;

    float get_val() override {
        return a.get_val() + b.get_val();
    }

    void backward(float _grad) override {
        a.backward(_grad);
        b.backward(_grad);
    }
};

class SubOperator : public AbstractOperator {
public:
    using AbstractOperator::AbstractOperator;

    float get_val() override {
        return a.get_val() - b.get_val();
    }

    void backward(float _grad) override {
        a.backward(_grad);
        b.backward(-_grad);
    }
};

class MulOperator : public AbstractOperator {
public:
    using AbstractOperator::AbstractOperator;

    float get_val() override {
        return a.get_val() * b.get_val();
    }

    void backward(float _grad) override {
        a.backward(_grad * b.get_val());
        b.backward(_grad * a.get_val());
    }
};

class DivOperator : public AbstractOperator {
public:
    using AbstractOperator::AbstractOperator;

    float get_val() override {
        return a.get_val() / b.get_val();
    }

    void backward(float _grad) override {
        a.backward(_grad / b.get_val());
        b.backward(-_grad * a.get_val() / (b.get_val() * b.get_val()));
    }
};

Node operator+(const Node &x, const Node &y) {
    return Node(std::make_shared<AddOperator>(x, y));
}

Node operator-(const Node &x, const Node &y) {
    return Node(std::make_shared<SubOperator>(x, y));
}

Node operator*(const Node &x, const Node &y) {
    return Node(std::make_shared<MulOperator>(x, y));
}

Node operator/(const Node &x, const Node &y) {
    return Node(std::make_shared<DivOperator>(x, y));
}
