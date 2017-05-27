#pragma once

#include "Glue.hpp"

using namespace std;


namespace BoxModel
{
	class HGlue : public Glue
	{
	public:
		HGlue(int cardinality, double size, double shrink, double stretch)
			: Glue(cardinality, size, shrink, stretch)
		{
		}


		void dump(ostream &out, int level)
		{
			(void)level;
			out << "<-" << string(cardinality, '-') << '>';
		}


		double getActualSize()
		{
			return width;
		}


		void setActualSize(double size)
		{
			width = size;
		}


		void writePSOutput(PS::Writer &writer)
		{
			writer.writeTd(width, 0);
		}
	};
}
