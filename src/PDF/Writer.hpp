#pragma once

#include <iomanip>
#include <map>
#include <ostream>
#include <string>

using namespace std;


namespace PDF
{
	class Writer
	{
		const string EOL = "\r\n";

		ostream &out;
		int indent = 0;
		string version;
		bool indentNextWrite = true;

		map<int, int> xrefEntries;
		int xrefOffset = 0;

		void indentCurrentLine()
		{
			if (indentNextWrite)
				out << string(indent, '\t');
		}


	public:
		Writer(ostream &out, string version = "1.4") : out(out)
		{
			this->version = version;
		}


		void writePDFHeader()
		{
			/* http://stackoverflow.com/questions/23433650 */
			string binaryDetect = "\r%\xE2\xE3\xCF\xD3";
			out << "%PDF-" << version << binaryDetect;
			writeEOL();
		}


		void writeEOL()
		{
			out << EOL;
			indentNextWrite = true;
		}


		void writeEOF()
		{
			out << "%%EOF";
			writeEOL();
		}


		void write(string code)
		{
			indentCurrentLine();
			out << code;
			
			if (code.length() > 0)
				indentNextWrite = false;
		}


		void writeLine(string code)
		{
			indentCurrentLine();
			out << code;
			writeEOL();
		}


		void
		addXrefEntry(int objID)
		{
			xrefEntries.emplace(objID, out.tellp());
		}


		void increaseIndent()
		{
			this->indent++;
		}


		void decreaseIndent()
		{
			this->indent--;
		}


		void writeXrefTable()
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
		writeStartXref()
		{
			out << "startxref" << EOL << xrefOffset << EOL;
		}
	};
}
