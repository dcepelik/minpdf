#include "Page.hpp"

using namespace PDF;


Page::Page(string code)
{
	this->code = code;
}


string
Page::contents()
{
	return this->code;
}
