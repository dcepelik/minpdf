#include <iomanip>

#include "Writer.hpp"

using namespace PDF;


void
Writer::indentCurrentLine()
{
	if (indentNextWrite)
		out << string(indent, '\t');
}


Writer::Writer(ostream &out, string version) : out(out)
{
	this->version = version;
}


void
Writer::writePDFHeader()
{
	/* http://stackoverflow.com/questions/23433650 */
	string binaryDetect = "\r%\xE2\xE3\xCF\xD3";
	out << "%PDF-" << version << binaryDetect;
	writeEOL();
}


void
Writer::writeEOL()
{
	out << EOL;
	indentNextWrite = true;
}


void
Writer::writeEOF()
{
	out << "%%EOF";
	writeEOL();
}


void
Writer::write(string code)
{
	indentCurrentLine();
	out << code;
	
	if (code.length() > 0)
		indentNextWrite = false;
}


void
Writer::writeLine(string code)
{
	indentCurrentLine();
	out << code;
	writeEOL();
}


void
Writer::addXrefEntry(int objID)
{
	xrefEntries.emplace(objID, out.tellp());
}


void
Writer::increaseIndent()
{
	this->indent++;
}


void
Writer::decreaseIndent()
{
	this->indent--;
}


void
Writer::writeXrefTable()
{
	xrefOffset = out.tellp();

	/* assuming xrefEntry keys are contiguous and start with 1 0 obj */
	out << "xref"
		<< EOL
		<< 0
		<< " "
		<< (xrefEntries.size() + 1) /* + 1 for `0 0 obj' */
		<< EOL;

	/* write `0 0 obj' */
	out << "0000000000 65535 f"
		<< EOL;

	for (auto xrefEntry: xrefEntries) {
		out << setfill('0')
			<< setw(10)
			<< xrefEntry.second
			<< " "
			<< setw(5)
			<< 0
			<< " n"
			<< EOL;
	}
}


void
Writer::writeStartXref()
{
	out << "startxref" << EOL << xrefOffset << EOL;
}
