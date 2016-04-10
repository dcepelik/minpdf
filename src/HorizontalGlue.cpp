#include <iostream>

#include "HorizontalGlue.hpp"

using namespace std;


void
HorizontalGlue::dump()
{
	cout << "#HGlue#";
}


void
HorizontalGlue::print(ostream &out) const
{
	(void)out;
	/* do whatever */
}


int
HorizontalGlue::getWidth()
{
	return 20;
}


int
HorizontalGlue::getStretchability()
{
	return 1000;
}
