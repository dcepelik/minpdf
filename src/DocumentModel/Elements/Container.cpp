#include <iostream>
#include <memory>
#include <vector>

#include "Container.hpp"

using namespace BoxModel;
using namespace DocumentModel;
using namespace DocumentModel::Elements;
using namespace std;


Container::Container(shared_ptr<Element> parent, string name) : Element(parent, name) {}


void
Container::addChild(shared_ptr<Element> child)
{
	children.push_back(shared_ptr<Element>(move(child)));
}


void
Container::render(vector<shared_ptr<Box>> &boxes)
{
	for (auto it = children.begin(); it != children.end(); it++) {
		(*it)->render(boxes);
	}
}


void
Container::dump(int level)
{	
	Element::dump(level);

	for (auto elem = children.begin(); elem != children.end(); elem++) {
		(*elem)->dump(level + 1);
	}
}


void
Container::removeEmptyChildren()
{
	auto it = children.begin();

	while (it != children.end()) {
		if ((*it)->empty()) {
			it = children.erase(it);
		}
		else {
			(*it)->removeEmptyChildren();
			it++;
		}
	}
}


bool
Container::empty()
{
	for (auto child = children.begin(); child != children.end(); child++) {
		if (!(*child)->empty()) {
			return false;
		}
	}

	return true;
}
