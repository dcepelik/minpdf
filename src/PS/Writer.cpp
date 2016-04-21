#include "Writer.hpp"

using namespace PS;
using namespace std;


Writer::Writer(ostream &out) : out(out)
{
}


void
Writer::writeLine(string code)
{
	out << code << EOL;
}


void
Writer::writeTd(int x, int y)
{
	out << x << " " << y << " Td" << EOL;
}


void
Writer::writeTf(string fontName, int fontSize)
{
	out << fontName << " " << fontSize << " Tf" << EOL;
}


void
Writer::writeTj(string text)
{
	out << '(' << text << ")Tj" << EOL;
}
