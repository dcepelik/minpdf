#include "Array.hpp"

using namespace PDF::Objects;
using namespace std;


void
Array::printInternal(ostream &out) const
{
	out << "[" << "\r\n";
	
	for (auto it = children.begin(); it != children.end(); it++) {
		(*it)->print(out);
	}

	out << "]" << "\r\n";
}


void
Array::addChild(shared_ptr<Object> obj)
{
	children.push_back(obj);
}
