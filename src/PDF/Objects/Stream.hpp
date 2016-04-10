#pragma once

#include <string>

#include "Object.hpp"

using namespace std;


namespace PDF
{
	namespace Objects
	{
		class Stream : public Object
		{
			string content;

			virtual void printInternal(ostream &out) const;

		public:
			Stream();
			Stream(string content);
		};
	}
}
