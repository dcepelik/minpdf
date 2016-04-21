#include "VGlue.hpp"

using namespace BoxModel;


VGlue::VGlue(int cardinality, int size, int shrink, int stretch)
	: Glue(cardinality, size, shrink, stretch) {}


int
VGlue::getActualSize()
{
	return height;
}


void
VGlue::setActualSize(int size)
{
	height = size;
}


void
VGlue::dump(ostream &out, int level)
{
	out << string(level, '\t') << '^' << cardinality << '^' << endl;
}


void
VGlue::writePSOutput(PS::Writer &writer)
{
	writer.writeTd(0, -height);
}
