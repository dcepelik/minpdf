#pragma once

#include "Glue.hpp"

using namespace std;


namespace BoxModel
{
	class VGlue : public Glue
	{
	public:
		VGlue(int cardinality, double size, double shrink, double stretch)
			: Glue(cardinality, size, shrink, stretch) {}


		double getActualSize()
		{
			return height;
		}


		void setActualSize(double size)
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
