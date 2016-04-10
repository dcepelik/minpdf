#pragma once

#include <string>

#include "Object.hpp"

using namespace std;


namespace PDF
{
	namespace Objects
	{
		class Literal : public Object
		{
			string code;

			virtual void printInternal(ostream &stream) const;

		public:
			Literal(string code);
		};
	}
}
