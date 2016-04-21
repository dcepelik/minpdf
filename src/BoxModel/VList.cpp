#include "VList.hpp"

using namespace BoxModel;


VList::VList(int size) : List(size) {};


int
VList::getBoxSize(shared_ptr<Box> box)
{
	return box->getHeight();
}


int
VList::getMaxListSize()
{
	return maxSize;
}


void
VList::dump(ostream &out, int level)
{
	out << string(level, '\t') << "^^[" << endl;

	for (auto child: children)
		child->dump(out, level + 1);

	out << string(level, '\t') << ']' << endl;
}


void
VList::writePSOutput(PS::Writer &writer)
{
	divideSpaces();

	List::writePSOutput(writer);
	writer.writeTd(-612, -getMaxListSize());
}
