#include <iostream>
#include <string>

#include "Element.hpp"

using namespace std;


Element::Element(string name)
{
	this->name = name;
}


void
Element::expand()
{
	/* by default, element will not produce any boxes */
}


void
Element::removeEmptyChildren()
{
	/* element has no children */
}


bool
Element::empty()
{
	return false;
}


void
Element::dump(int level)
{
	string tabs(level, '\t');
	cout << tabs << "Element [" << name << "]:" << endl;
}

