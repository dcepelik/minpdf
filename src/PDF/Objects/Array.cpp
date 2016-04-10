#include "Array.hpp"

using namespace PDF::Objects;
using namespace std;


void
Array::printInternal(ostream &out) const
{
	out << "[" << endl;
	
	for (auto it = children.begin(); it != children.end(); it++) {
		(*it)->print(out);
	}

	out << "]" << endl;
}


void
Array::addChild(shared_ptr<Object> obj)
{
	children.push_back(obj);
}
