#include "BoxModel/Container.hpp"

using namespace BoxModel;
using namespace std;


Container::Container() : Box(0, 0) {}


void
Container::addChild(shared_ptr<Box> child)
{
	children.push_back(child);
}


void
Container::dump()
{
	cout << "HList{ ";
	
	for (auto child: children) {
		child->dump();
	}

	cout << " }";
}
