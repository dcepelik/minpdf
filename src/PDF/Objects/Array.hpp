#pragma once

#include <vector>
#include <memory>

#include "Object.hpp"

using namespace std;


namespace PDF
{
	namespace Objects
	{
		class Array : public Object
		{
			vector<Object *> children;

		public:
			void addChild(Object *obj);

			void writePDFOutput(Writer &writer);
		};
	}

}
