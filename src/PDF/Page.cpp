#include "Page.hpp"

using namespace PDF;


Page::Page(string code)
{
	this->code = code;
}


string
Page::contents()
{
	return "BT\r\n" + this->code + "ET\r\n";
}
