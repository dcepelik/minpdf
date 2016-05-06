#pragma once

#include "Box.hpp"

using namespace std;


namespace BoxModel
{
	class Char : public Box
	{
		char c;
		string fontFamily;
		int fontSize;

	public:
		Char(char c, string fontFamily, int fontSize)
		{
			this->c = c;
			this->fontFamily = fontFamily;
			this->fontSize = fontSize;

			width = fontSize / 2;
			height = fontSize * 1.2;
		}


		void dump(ostream &out, int level)
		{
			(void)level;
			out << c;
		}


		void writePSOutput(PS::Writer &writer)
		{	
			writer.writeTf(fontFamily, fontSize);
			writer.writeTj(string(1, c));
			writer.writeTd(this->width, 0);
		}
	};
}
