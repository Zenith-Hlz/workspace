#pragma once
#include <list>
#include <memory>

class MyList
{
private:
	std::shared_ptr<std::list<int>> pt;	  // a pointer to the real container
	std::list<int>::iterator left, right; // the position of slice is [left, right). 'left' is included, 'right' is excluded.

	std::list<int>::iterator forward(int pos) const
	{
		// count from 'left', find the element at position 'pos'.
		auto now = left;
		while (pos--)
			now++;
		return now;
	}

public:
	MyList() : pt(new std::list<int>())
	{
		left = pt->begin();
		right = pt->end();
		// Actually, left = right = pt->end(), because there is no element in the list.
	}

	MyList(const MyList &other) : pt(other.pt), left(other.left), right(other.right)
	{
		// Copy constructor to handle reference-like behavior in Python
	}

	MyList(std::shared_ptr<std::list<int>> pt, std::list<int>::iterator left, std::list<int>::iterator right)
		: pt(pt), left(left), right(right) {}

	void append(int i)
	{
		pt->insert(right, i); // insert i just before 'right'. 'right' and 'left' will be still valid (because we use list, not vector).
		// DEBUG !! Why I can't insert i??
		if (left == right)
		{
			// If the list was empty, update left to point to the new element.
			left = right;
			left--;
		}
	}

	int operator[](int pos) const
	{
		return *forward(pos); // access the element at the 'pos'
	}

	int &operator[](int pos)
	{
		return *forward(pos); // access the element at the 'pos'
	}

	MyList operator()(int l, int r)
	{
		// Taking a slice [l, r)
		return MyList(pt, forward(l), forward(r));
	}

	friend std::ostream &operator<<(std::ostream &out, const MyList &obj)
	{
		obj.output(out);
		return out;
	}

	void output(std::ostream &out) const
	{
		out << "[";
		if (left != right)
		{
			auto now = left;
			out << *now;
			now++;
			for (; now != right; now++)
			{
				out << "," << *now;
			}
		}
		out << "]";
	}
};