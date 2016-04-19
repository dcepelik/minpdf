#include <iostream>

#include "Char.hpp"

using namespace BoxModel;


Char::Char(char c) : Box(13, 25)
{
	this->c = c;
}


void
Char::dump()
{
	cout << c;
}


BoxType
Char::getType()
{
	return BoxType::CharBox;
}



void
Char::writePSOutput(ostream &out)
{
	out << "/F1 24 Tf\r\n(" << c << ") Tj\r\n";
	out << width << " 0 Td\r\n";
}
