#include "Object.hpp"


void
PDF::Objects::Object::print(ostream &out) const
{
	printInternal(out);
}


ostream& operator<<(ostream &out, const PDF::Objects::Object &obj)
{
	obj.print(out);
	return out;
}

