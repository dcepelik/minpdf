#include "IndirectObject.hpp"

using namespace PDF::Objects;
using namespace PDF;
using namespace std;


template<class T>
void
IndirectObject<T>::writePDFOutput(Writer &writer)
{
	writer.addXrefEntry(id);

	writer.writeLine(to_string(id) + " " + to_string(revision) + " obj");
	writer.increaseIndent();
	wrappedObject->writePDFOutput(writer);
	writer.decreaseIndent();
	writer.writeLine("endobj");
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


template<class T>
int
IndirectObject<T>::getID()
{
	return id;
}


/* @todo http://stackoverflow.com/questions/8752837 */

#include "Dictionary.hpp"
#include "Stream.hpp"

template class IndirectObject<Dictionary>;
template class IndirectObject<Stream>;
