#pragma once

#include <string>

#include "Object.hpp"

using namespace PDF;
using namespace std;


namespace PDF
{
	namespace Objects
	{
		class Name : public Object
		{
			string name;

		public:
			Name(string name);

			void writePDFOutput(Writer &writer);
		};
	}
}
