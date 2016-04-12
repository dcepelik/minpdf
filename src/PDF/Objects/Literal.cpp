#include "Literal.hpp"

using namespace PDF::Objects;
using namespace PDF;
using namespace std;


Literal::Literal(string code)
{
	this->code = code;
}


void
Literal::writePDFOutput(Writer &writer)
{
	writer.write(code);
}
