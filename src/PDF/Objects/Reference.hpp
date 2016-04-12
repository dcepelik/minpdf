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

		public:
			Reference(int id, int revision);

			void writePDFOutput(Writer &writer);
		};
	}
}
