#include <sstream>

#include "Reference.hpp"

using namespace PDF::Objects;
using namespace PDF;


Reference::Reference(int id, int revision)
{
	this->id = id;
	this->revision = revision;
}


void
Reference::writePDFOutput(Writer &writer)
{
	writer.writeLine(to_string(id) + " " + to_string(revision) + " R");
}
