#include "LineBreak.hpp"

using namespace BoxModel;


LineBreak::LineBreak() : Box(0, 0) {}


BoxType
LineBreak::getType()
{
	return BoxType::LineBreakBox;
}


void
LineBreak::writePSOutput(ostream &out)
{
	static int counter;

	out << "1 0 0 1 0 " << 725 - counter++ * 25 << " Tm\r\n";
}


void
LineBreak::dump()
{
	cout << "\\n" << endl;
}
