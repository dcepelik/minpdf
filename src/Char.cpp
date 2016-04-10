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
