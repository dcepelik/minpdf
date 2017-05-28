#pragma once

#include "Box.hpp"

using namespace std;


namespace BoxModel
{
	class InlinePostscript : public Box
	{
		string ps;

	public:
		InlinePostscript(string ps) : Box(0, 0)
		{
			this->ps = ps;
		}


		void dump(ostream &out, int level)
		{
			(void) out;
			(void) level;
			/* TODO create some output when dumping this */
		}


		void writePSOutput(PS::Writer &writer)
		{	
			writer.writeLine(ps);
		}
	};
}
