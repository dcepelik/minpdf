#pragma once

#include "Box.hpp"

using namespace std;


namespace BoxModel
{
	class Line : public Box
	{
		double width;
		double relX;
		double relY;

	public:
		Line(double width, double relX, double relY)
		{
			this->width = width;
			this->relX = relX;
			this->relY = relY;
		}

		Line() : Line(0, 0, 0)
		{
		}


		void dump(ostream &out, int level)
		{
			(void) out;
			(void) level;
			/* TODO */
		}


		void writePSOutput(PS::Writer &writer)
		{	
			writer.writeLine(to_string(writer.getX() + relX) + " " + to_string(writer.getY() + relY) + " m");
			writer.writeLine(to_string(writer.getX() + width) + " " + to_string(writer.getY()) + " l");
			writer.writeLine("s");
			writer.writeTd(0, -4);
		}
	};
}
