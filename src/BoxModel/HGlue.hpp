#pragma once

#include "Glue.hpp"

using namespace std;


namespace BoxModel
{
	class HGlue : public Glue
	{
	public:
		HGlue(int cardinality, int width, int shrink, int stretch);

		int getActualSize();
		void setActualSize(int size);

		void dump(ostream &out, int level = 0);
		void writePSOutput(PS::Writer &writer);
	};
}
