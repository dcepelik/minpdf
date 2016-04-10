#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Box.hpp"

using namespace std;


class Element
{
	string name;
	Element();

public:
	Element(string name);
	virtual void expand(vector<shared_ptr<Box>> &boxes);
	virtual void dump(int level = 0);
	virtual void removeEmptyChildren();
	virtual bool empty();
};
