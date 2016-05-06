#pragma once

#include "Glue.hpp"

using namespace std;


namespace BoxModel
{
	class HGlue : public Glue
	{
	public:
		HGlue(int cardinality, int size, int shrink, int stretch)
			: Glue(cardinality, size, shrink, stretch)
		{
		}


		void dump(ostream &out, int level)
		{
			(void)level;
			out << "<-" << string(cardinality, '-') << '>';
		}


		int getActualSize()
		{
			return width;
		}


		void setActualSize(int size)
		{
			width = size;
		}


		void writePSOutput(PS::Writer &writer)
		{
			writer.writeTd(width, 0);
		}
	};
}
