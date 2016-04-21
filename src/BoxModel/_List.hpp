#pragma once

#include <vector>

#include "Container.hpp"

namespace BoxModel
{
	class List : public Container
	{
	public:
		List();

		BoxType getType();

		void dump(ostream &out, int level = 0);
		void writePSOutput(PS::Writer &writer);
	};
}
