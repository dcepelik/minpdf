#pragma once

#include "Glue.hpp"

using namespace std;


namespace BoxModel
{
	class VGlue : public Glue
	{
	public:
		VGlue(int cardinality, int height, int shrink, int stretch);

		int getActualSize();
		void setActualSize(int size);

		void dump(ostream &out, int level = 0);
		void writePSOutput(PS::Writer &writer);
	};
}
