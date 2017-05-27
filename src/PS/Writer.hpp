#pragma once

#include <ostream>

using namespace std;


namespace PS
{
	class Writer
	{
		ostream &out;

		const string EOL = "\r\n";

	public:
		Writer(ostream &out) : out(out)
		{
		}


		void writeLine(string code)
		{
			out << code << EOL;
		}


		//void writeTd(int x, int y)
		//{
		//	out << x << " " << y << " Td" << EOL;
		//}


		void writeTd(double x, double y)
		{
			out << x << " " << y << " Td" << EOL;
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
