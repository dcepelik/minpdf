#include "Reference.hpp"

using namespace PDF::Objects;


Reference::Reference(int id, int revision)
{
	this->id = id;
	this->revision = revision;
}


void
Reference::printInternal(ostream &out) const
{
	out << id << " " << revision << " R" << endl;
}
