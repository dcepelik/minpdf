#pragma once

#include "Box.hpp"

using namespace std;


namespace BoxModel
{
	class Line : public Box
	{
		double relX;
		double relY;
		bool clear;

	public:
		Line(double width, double relX, double relY, bool clear)
			: Box(width, 4)
		{
			this->relX = relX;
			this->relY = relY;
			this->clear = clear;
		}

		Line() : Line(0, 0, 0, true)
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
			writer.writeLine(to_string(writer.getX() + width + relX) + " " + to_string(writer.getY() + relY) + " l");
			writer.writeLine("s");

			if (clear)
				writer.writeTd(0, -4);
			else
				writer.writeTd(width, 0);
		}
	};
}
