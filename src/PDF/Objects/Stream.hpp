#pragma once

#include <string>

#include "Object.hpp"

using namespace PDF;
using namespace std;


namespace PDF
{
	namespace Objects
	{
		class Stream : public Object
		{
			string content;

		public:
			Stream();
			Stream(string content);

			void writePDFOutput(Writer &writer);
		};
	}
}
