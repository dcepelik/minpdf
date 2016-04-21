#include "HList.hpp"

using namespace BoxModel;


HList::HList(int maxSize) : List(maxSize) {};


int
HList::getBoxSize(shared_ptr<Box> el)
{
	return el->getWidth();
}


int
HList::getMaxListSize()
{
	return maxSize; /* TODO */
}


void
HList::dump(ostream &out, int level)
{
	out << string(level, '\t') << "<->[";
	
	for (auto child: children)
		child->dump(out, level + 1);

	out << string(level, '\t') << ']' << endl;
}


void
HList::writePSOutput(PS::Writer &writer)
{
	divideSpaces();

	List::writePSOutput(writer);
	writer.writeTd(-getMaxListSize(), -15); /* TODO */
}
