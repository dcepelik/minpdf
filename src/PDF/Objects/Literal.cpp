#include "Literal.hpp"

using namespace PDF::Objects;
using namespace std;


Literal::Literal(string code)
{
	this->code = code;
}


void
Literal::printInternal(ostream &out) const
{
	out << code << "\r\n";
}
