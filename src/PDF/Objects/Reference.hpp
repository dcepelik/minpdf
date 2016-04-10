#pragma once

#include "Object.hpp"


namespace PDF
{
	namespace Objects
	{
		class Reference : public Object
		{
			int id;
			int revision;

			virtual void printInternal(ostream &out) const;

		public:
			Reference(int id, int revision);
		};
	}
}
