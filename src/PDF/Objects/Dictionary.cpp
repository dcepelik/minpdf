#include "Dictionary.hpp"

using namespace PDF::Objects;
using namespace std;


void
Dictionary::printInternal(ostream &out) const
{
	out << "<<" << endl;

	for (auto &item: items) {
		out << "/" << item.first << " " << (*item.second);
	}

	out << ">>" << endl;
}


void
Dictionary::addItem(string key, shared_ptr<Object> value)
{
	items.emplace(key, value);
}
