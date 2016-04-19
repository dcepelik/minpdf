#include <iostream>
#include <stdexcept>
#include <string>

#include "Element.hpp"
#include "BoxModel/Box.hpp"

using namespace BoxModel;
using namespace DocumentModel::Elements;
using namespace std;


Element::Element(string name)
{
	this->name = name;
}


void
Element::addChild(shared_ptr<Element> child)
{
	(void)child;
	throw new domain_error("Cannot add children to non-containers");
}


void
Element::render(vector<shared_ptr<Box>> &boxes)
{
	/* by default, element will not produce any boxes */
	(void)boxes;
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

