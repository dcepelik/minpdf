#pragma once

#include <memory>
#include <unordered_map>

#include "Name.hpp"
#include "Object.hpp"

using namespace PDF;
using namespace std;


namespace PDF
{
	namespace Objects
	{
		class Dictionary : public Object
		{
			unordered_map<string, Object *> items;

		public:
			void addItem(string name, Object *obj);
			void addItem(string name, shared_ptr<Object> ptr);

			void writePDFOutput(Writer &writer);
		};
	}
}
