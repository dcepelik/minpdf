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
	cout << endl << string('\t', level) << string('^', cardinality) << endl;
}


void
VGlue::writePSOutput(PS::Writer &writer)
{
	/* TODO */
}
