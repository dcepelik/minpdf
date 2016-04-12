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
			unordered_map<string, shared_ptr<Object>> items;

		public:
			void addItem(string key, shared_ptr<Object> value);
			void addItem(string key, Object *value);
			void writePDFOutput(Writer &writer);
		};
	}
}
