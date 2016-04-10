#include "Name.hpp"

using namespace PDF::Objects;
using namespace std;


Name::Name(string name)
{
	this->name = name; /* @todo check name is valid */
}


void
Name::printInternal(ostream &out) const
{
	out << "/" << name << endl;
}
