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
			Literal(string code)
			{
				this->code = code;
			}


			void writePDFOutput(Writer &writer)
			{
				writer.write(code); /* be verbatim: don't add an EOL */
			}
		};
	}
}
