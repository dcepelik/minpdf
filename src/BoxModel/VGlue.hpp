#pragma once

#include "Glue.hpp"

using namespace std;


namespace BoxModel
{
	class VGlue : public Glue
	{
	public:
		VGlue(int cardinality, int size, int shrink, int stretch)
			: Glue(cardinality, size, shrink, stretch) {}


		int getActualSize()
		{
			return height;
		}


		void setActualSize(int size)
		{
			height = size;
		}


		void dump(ostream &out, int level)
		{
			out << string(level, '\t') << '^' << cardinality << '^' << endl;
		}


		void writePSOutput(PS::Writer &writer)
		{
			writer.writeTd(0, -height);
		}
	};
}
