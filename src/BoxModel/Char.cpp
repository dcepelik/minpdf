#include <iostream>

#include "Char.hpp"

using namespace BoxModel;


Char::Char(char c) : Box(15, 30)
{
	this->c = c;
}


BoxType
Char::getType()
{
	return BoxType::Char;
}
