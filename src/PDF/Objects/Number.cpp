#include "Number.hpp"

using namespace PDF::Objects;
using namespace PDF;


Number::Number(int number)
{
	this->number = number;
}


void
Number::writePDFOutput(Writer &writer)
{
	writer.write(to_string(number));
}
