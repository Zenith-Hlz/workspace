#pragma once

class AbstractNode {
    static int count;
public:
    virtual float get_val() = 0;
    virtual void backward(float _grad) = 0;

    AbstractNode();
    AbstractNode(const AbstractNode &n);
    AbstractNode(AbstractNode &&n);
    AbstractNode& operator = (const AbstractNode &n) = default;
    AbstractNode& operator = (AbstractNode &&n) = default;
    virtual ~AbstractNode();
    static int get_count();
};