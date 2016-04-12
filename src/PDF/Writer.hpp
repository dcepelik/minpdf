#pragma once

#include <ostream>
#include <string>
#include <unordered_map>

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
		unordered_map<int, int> xrefEntries;

		void indentCurrentLine();

	public:
		Writer(ostream &out, string version = "1.7");

		void writePDFHeader();
		void writeEOL();
		void writeEOF();

		void write(string code);
		void writeLine(string code);

		void increaseIndent();
		void decreaseIndent();

		void addXrefEntry(int objID);
	};
}
