#pragma once

#include "Object.hpp"

using namespace PDF;

namespace PDF
{
	namespace Objects
	{
		class Number : public Object
		{
			int number;

		public:
			Number(int number)
			{
				this->number = number;
			}


			void writePDFOutput(Writer &writer)
			{
				writer.writeLine(to_string(number));
			}
		};
	}
}
