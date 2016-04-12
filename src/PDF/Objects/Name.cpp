#include "Name.hpp"

using namespace PDF::Objects;
using namespace PDF;
using namespace std;


Name::Name(string name)
{
	this->name = name; /* @todo check name is valid */
}


void
Name::writePDFOutput(Writer &writer)
{
	writer.writeLine("/" + name);
}
