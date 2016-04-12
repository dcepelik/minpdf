#pragma once

#include <string>

#include "Object.hpp"

using namespace PDF;
using namespace std;


namespace PDF
{
	namespace Objects
	{
		class Literal : public Object
		{
			string code;

		public:
			Literal(string code);

			void writePDFOutput(Writer &writer);
		};
	}
}
