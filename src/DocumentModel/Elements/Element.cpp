#include <iostream>
#include <stdexcept>
#include <string>

#include "DocumentModel/Document.hpp"
#include "Element.hpp"

using namespace DocumentModel::Elements;
using namespace DocumentModel;
using namespace std;


Element::Element(shared_ptr<Element> parent, string name)
{
	this->parent = parent;
	this->name = name;
}


void
Element::addChild(shared_ptr<Element> child)
{
	(void)child;
	throw new domain_error("Cannot add children to non-containers");
}


shared_ptr<Element>
Element::getParent()
{
	return parent;
}


Document *
Element::getDocument()
{
	shared_ptr<Element> p = parent;
	while (p.get() != NULL) {
		Document *doc;
		if ((doc = dynamic_cast<Document *>(p.get()))) {
			return doc;
		}

		p = p->getParent();
	}

	return NULL;
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

