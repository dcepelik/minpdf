#pragma once

#include <memory>

#include "Object.hpp"
#include "Reference.hpp"

using namespace PDF;
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

			void setupID();

		public:
			IndirectObject();
			IndirectObject(shared_ptr<T> wrappedObject);

			shared_ptr<T> wrapped();
			shared_ptr<Reference> getRef();

			void writePDFOutput(Writer &writer);

			int getID();
		};
	}
}
