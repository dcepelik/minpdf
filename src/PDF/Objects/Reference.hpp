#pragma once

#include <sstream>

#include "Object.hpp"

namespace PDF
{
	namespace Objects
	{
		class Reference : public Object
		{
			int id;
			int revision;

		public:
			Reference(int id, int revision)
			{
				this->id = id;
				this->revision = revision;
			}


			void writePDFOutput(Writer &writer)
			{
				writer.writeLine(to_string(id) + " " + to_string(revision) + " R");
			}
		};
	}
}
