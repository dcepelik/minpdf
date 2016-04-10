#include "IndirectObject.hpp"

using namespace PDF::Objects;
using namespace std;


template<class T>
void
IndirectObject<T>::printInternal(ostream &out) const
{
	out << id << " " << revision << " obj" << endl;
	wrappedObject->print(out);
	out << "endobj" << endl;
}


template<class T>
void
IndirectObject<T>::setupID()
{
	this->id = ++counter;
	this->revision = 0; /* revisions are not supported */
}


template<class T>
IndirectObject<T>::IndirectObject(shared_ptr<T> wrappedObject)
{
	setupID();
	this->wrappedObject = wrappedObject;
}


template<class T>
IndirectObject<T>::IndirectObject()
{
	setupID();
	this->wrappedObject = shared_ptr<T>(new T());
}



template<class T>
shared_ptr<T>
IndirectObject<T>::wrapped()
{
	return wrappedObject;
}



template<class T>
shared_ptr<Reference>
IndirectObject<T>::getRef()
{
	return shared_ptr<Reference>(new Reference(this->id, this->revision));
}


/* @todo http://stackoverflow.com/questions/8752837 */

#include "Dictionary.hpp"
#include "Stream.hpp"

template class IndirectObject<Dictionary>;
template class IndirectObject<Stream>;
