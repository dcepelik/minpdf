#include "Object.hpp"


int PDF::Objects::Object::counter = 0;


void
PDF::Objects::Object::print(ostream &out) const
{
	printInternal(out);
}


int
PDF::Objects::Object::objectCount()
{
	return PDF::Objects::Object::counter;
}


ostream& operator<<(ostream &out, const PDF::Objects::Object &obj)
{
	obj.print(out);
	return out;
}

