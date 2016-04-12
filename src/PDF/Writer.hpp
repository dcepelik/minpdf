#pragma once

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

		void indentCurrentLine();

	public:
		Writer(ostream &out, string version = "1.7");

		void writePDFHeader();
		void writeEOL();

		void write(string code);
		void writeLine(string code);

		void increaseIndent();
		void decreaseIndent();

		void addXrefEntry(int objID);

		void writeXrefTable();
		void writeStartXref();
		void writeEOF();
	};
}
