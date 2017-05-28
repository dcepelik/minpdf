#pragma once

#include <ostream>

using namespace std;


namespace PS
{
	class Writer
	{
		ostream &out;

		const string EOL = "\r\n";
		double x = 0;
		double y = 0;

	public:
		Writer(ostream &out) : out(out)
		{
		}


		double getX()
		{
			return x;
		}


		double getY()
		{
			return y;
		}


		void writeLine(string code)
		{
			out << code << EOL;
		}


		void writeTd(double x, double y)
		{
			out << x << " " << y << " Td" << EOL;
			this->x += x;
			this->y += y;
		}


		void writeTf(string fontName, int fontSize)
		{
			out << fontName << " " << fontSize << " Tf" << EOL;
		}


		void writeTj(string text)
		{
			out << '(' << text << ")Tj" << EOL;
		}
	};
}
