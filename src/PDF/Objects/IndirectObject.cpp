#include "IndirectObject.hpp"

using namespace PDF::Objects;
using namespace std;


void
IndirectObject::printInternal(ostream &out) const
{
	out << id << " " << revision << "obj" << endl;
	wrappedObject->print(out);
	out << "endobj" << endl;
}


IndirectObject::IndirectObject(int id, shared_ptr<Object> wrappedObject)
{
	this->id = id;
	this->wrappedObject = wrappedObject;

	this->revision = 0; /* revisions are not supported */
}
