#pragma once

#include <memory>
#include <vector>

#include "Box.hpp"
#include "Element.hpp"

using namespace std;


class Container : public Element
{
	string name;

public:
	vector<shared_ptr<Element>> children;

	Container(string name);
	void expand(vector<shared_ptr<Box>> &boxes);
	virtual void dump(int level = 0);
	virtual void removeEmptyChildren();
	virtual bool empty();
};
