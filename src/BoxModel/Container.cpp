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
Container::dump(ostream &out, int level)
{
	out << string('\t', level) << '{';

	for (auto child: children)
		child->dump(out, level + 1);

	out << string('\t', level) << '}';
}


void
Container::writePSOutput(PS::Writer &writer)
{
	for (auto child: children)
		child->writePSOutput(writer);
}
