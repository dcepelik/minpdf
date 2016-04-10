#pragma once

#include <memory>

#include "Object.hpp"
#include "Reference.hpp"

using namespace std;


namespace PDF
{
	namespace Objects
	{
		template <class T>
		class IndirectObject : public Object
		{
			int id;
			int revision;
			shared_ptr<T> wrappedObject;

			virtual void printInternal(ostream &out) const;
			void setupID();

		public:
			IndirectObject();
			IndirectObject(shared_ptr<T> wrappedObject);

			shared_ptr<T> wrapped();
			shared_ptr<Reference> getRef();
		};
	}
}
