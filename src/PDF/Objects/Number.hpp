#pragma once

#include "Object.hpp"


namespace PDF
{
	namespace Objects
	{
		class Number : public Object
		{
			int number;

			virtual void printInternal(ostream &out) const;

		public:
			Number(int number);
		};
	}
}
