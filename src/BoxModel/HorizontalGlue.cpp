#include <iostream>

#include "HorizontalGlue.hpp"

using namespace BoxModel;


HorizontalGlue::HorizontalGlue() : Box(20, 0) {}


void
HorizontalGlue::dump()
{
	cout << "#";
}


void
HorizontalGlue::writePSOutput(ostream &out)
{
	out << width << " 0 Td\r\n";
}


BoxType
HorizontalGlue::getType()
{
	return BoxType::HorizontalGlueBox;
}
