#pragma once

#include <string>

#include "Object.hpp"

using namespace std;


namespace PDF
{
	namespace Objects
	{
		class Name : public Object
		{
			string name;

			virtual void printInternal(ostream &stream) const;

		public:
			Name(string name);
		};
	}
}
