#pragma once

#include "Box.hpp"

using namespace std;


namespace BoxModel
{
	class LineBreak : public Box
	{
	public:
		LineBreak();

		void dump();
		void writePSOutput(ostream &out);
		BoxType getType();
	};
}
