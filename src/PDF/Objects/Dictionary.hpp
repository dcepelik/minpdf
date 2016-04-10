#pragma once

#include <unordered_map>
#include <memory>

#include "Object.hpp"
#include "Name.hpp"

using namespace std;


namespace PDF
{
	namespace Objects
	{
		class Dictionary : public Object
		{
			unordered_map<string, shared_ptr<Object>> items;

			virtual void printInternal(ostream &stream) const;

		public:
			void addItem(string key, shared_ptr<Object> value);
			void addItem(string key, Object *value);
		};
	}
}
