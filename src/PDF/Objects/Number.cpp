#include "Number.hpp"

using namespace PDF::Objects;


Number::Number(int number)
{
	this->number = number;
}


void
Number::printInternal(ostream &out) const
{
	out << number << "\r\n";
}
