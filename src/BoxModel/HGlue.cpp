#include "HGlue.hpp"

using namespace BoxModel;


HGlue::HGlue(int cardinality, int size, int shrink, int stretch)
	: Glue(cardinality, size, shrink, stretch) {}


void
HGlue::dump(ostream &out, int level)
{
	cout << "<-" << string(cardinality, '-') << '>';
}


int
HGlue::getActualSize()
{
	return width;
}


void
HGlue::setActualSize(int size)
{
	width = size;
}


void
HGlue::writePSOutput(PS::Writer &writer)
{
	writer.writeTd(width, 0);
}
