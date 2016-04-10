#include <iostream>

#include "Char.hpp"

using namespace std;


Char::Char(char c)
{
	this->c = c;
}


void
Char::dump()
{
	cout << "[" << c << "]";
}


void
Char::print(ostream &out) const
{
	out << "/F1 24 Tf\r\n";
	out << "1 0 0 1 " << x << " " << y << " Tm\r\n";
	out << "(" << c << ") Tj\r\n";
}


int
Char::getWidth()
{
	return 14;
}


int
Char::getStretchability()
{
	return 0;
}
