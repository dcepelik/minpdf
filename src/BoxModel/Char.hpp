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
		Char(char c, string fontFamily, int fontSize);

		void dump(ostream &out, int level = 0);
		void writePSOutput(PS::Writer &writer);
	};
}
