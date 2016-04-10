#pragma once

#include <memory>

#include "Object.hpp"

using namespace std;


namespace PDF
{
	namespace Objects
	{
		class IndirectObject : public Object
		{
			int id;
			int revision;
			shared_ptr<Object> wrappedObject;

			virtual void printInternal(ostream &out) const;

		public:
			IndirectObject(int id, shared_ptr<Object> wrappedObject);
		};
	}
}
