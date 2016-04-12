#pragma once

#include <memory>

#include "Object.hpp"
#include "Reference.hpp"

using namespace PDF;
using namespace PDF::Objects;
using namespace std;


namespace PDF
{
	namespace Objects
	{
		template <class T>
		class IndirectObject : public Object
		{
			T inner;

			int id;
			int revision;

			void setupID();

		public:
			IndirectObject();
			IndirectObject(T inner);

			T &getInner();
			unique_ptr<Reference> getReference();

			void writePDFOutput(Writer &writer);
		};
	}
}


template<class T>
void
IndirectObject<T>::writePDFOutput(Writer &writer)
{
	writer.addXrefEntry(id);

	writer.writeLine(to_string(id) + " " + to_string(revision) + " obj");
	writer.increaseIndent();

	inner.writePDFOutput(writer);

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
IndirectObject<T>::IndirectObject(T inner)
{
	setupID();
	this->inner = inner;
}


template<class T>
IndirectObject<T>::IndirectObject()
{
	setupID();
}



template<class T>
T &
IndirectObject<T>::getInner()
{
	return inner;
}



template<class T>
unique_ptr<Reference>
IndirectObject<T>::getReference()
{
	return unique_ptr<Reference>(new Reference(this->id, this->revision));
}
