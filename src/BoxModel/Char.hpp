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

			array<float, 256> charWidths;
			charWidths.fill(fontSize / 2.0);

			charWidths['a'] = 5.2;
			charWidths['b'] = 6.2;
			charWidths['c'] = 5.3;
			charWidths['b'] = 6.1;
			charWidths['d'] = 6;
			charWidths['e'] = 5.3;
			charWidths['f'] = 4.1;
			charWidths['g'] = 5.5;
			charWidths['h'] = 5.5;
			charWidths['i'] = 3.2;
			charWidths['j'] = 3.2;
			charWidths['k'] = 5.8;
			charWidths['l'] = 3.2;
			charWidths['m'] = 9.4;
			charWidths['o'] = 5.8;
			charWidths['p'] = 5.8;
			charWidths['n'] = 6;
			charWidths['r'] = 4;
			charWidths['s'] = 4.7;
			charWidths['t'] = 3.5;
			charWidths['u'] = 5.8;
			charWidths['v'] = 5.3;
			charWidths['w'] = 8.3;
			charWidths['y'] = 5.8;
			charWidths['z'] = 5.8;

			charWidths['A'] = 8;
			charWidths['B'] = 8;
			charWidths['C'] = 8;
			charWidths['B'] = 8;
			charWidths['D'] = 8;
			charWidths['E'] = 8;
			charWidths['F'] = 7;
			charWidths['G'] = 8;
			charWidths['H'] = 8;
			charWidths['I'] = 4;
			charWidths['J'] = 5;
			charWidths['K'] = 8.5;
			charWidths['L'] = 7.7;
			charWidths['M'] = 10.7;
			charWidths['N'] = 8.1;
			charWidths['O'] = 9;
			charWidths['P'] = 7;
			charWidths['Q'] = 9;
			charWidths['R'] = 8;
			charWidths['S'] = 7.5;
			charWidths['T'] = 8;
			charWidths['U'] = 8;
			charWidths['V'] = 8;
			charWidths['W'] = 10.5;
			charWidths['X'] = 8.3;
			charWidths['Y'] = 8.4;
			charWidths['Z'] = 8;

			charWidths['\''] = 1.5;
			charWidths[','] = 1.5;
			charWidths['+'] = 6.3;
			charWidths['.'] = 1.5;

			width = charWidths[c] * (fontSize / 12.0);
			height = fontSize;
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
