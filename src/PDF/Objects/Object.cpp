#include "Object.hpp"


int PDF::Objects::Object::counter = 0;


int
PDF::Objects::Object::objectCount()
{
	return PDF::Objects::Object::counter;
}
