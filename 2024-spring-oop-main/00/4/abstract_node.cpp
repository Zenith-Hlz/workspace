#include "abstract_node.h"

int AbstractNode::count = 0;

AbstractNode::AbstractNode() {
    count ++;
}
AbstractNode::AbstractNode(const AbstractNode &n) {
    count ++;
}
AbstractNode::AbstractNode(AbstractNode &&n) {
    count ++;
}
AbstractNode::~AbstractNode() {
    count --;
}
int AbstractNode::get_count() {
    return count;
}