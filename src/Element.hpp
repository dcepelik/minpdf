#pragma once

#include <string>

using namespace std;


class Element
{
	string name;
	Element();

public:
	Element(string name);
	virtual void expand();
	virtual void dump(int level = 0);
	virtual void removeEmptyChildren();
	virtual bool empty();
};
