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
			vector<shared_ptr<Object>> children;

		public:
			void addChild(shared_ptr<Object> obj);
			void writePDFOutput(Writer &writer);
		};
	}

}
