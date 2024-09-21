#include "Node.h"

int Node::createTimes = 0, Node::copyCreateTimes = 0, Node::moveCreateTimes = 0;
int Node::copyAssignTimes = 0, Node::moveAssignTimes = 0, Node::delTimes = 0;

Node::Node(int v) : val(v)
{
	createTimes++;
	std::cout << "createTimes" << createTimes << '\n';
}
Node::~Node()
{
	delTimes++;
}
Node::Node(const Node &y) : val(y.val)
{
	copyCreateTimes++;
	std::cout << "copyCreateTimes" << copyCreateTimes << '\n';
}
Node::Node(Node &&y) : val(y.val)
{
	y.val = 0;
	moveCreateTimes++;
	std::cout << "moveCreateTimes" << moveCreateTimes << '\n';
}
Node &Node::operator=(const Node &y)
{
	val = y.val;
	copyAssignTimes++;
	std::cout << "copyAssignTimes" << copyAssignTimes << '\n';
	return *this;
}
Node &Node::operator=(Node &&y)
{
	val = y.val;
	y.val = 0;
	moveAssignTimes++;
	std::cout << "moveAssignTimes" << moveAssignTimes << '\n';
	return *this;
}

std::istream &operator>>(std::istream &in, Node &x)
{
	in >> x.val;
	return in;
}
std::ostream &operator<<(std::ostream &out, const Node &x)
{
	out << x.val;
	return out;
}

void Node::outputResult()
{
	std::cout << Node::createTimes << " " << Node::copyCreateTimes << " " << Node::moveCreateTimes << " " << Node::copyAssignTimes << " " << Node::moveAssignTimes << " " << Node::delTimes << std::endl;
}