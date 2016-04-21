#pragma once

#include <ostream>

using namespace std;


namespace PS
{
	class Writer
	{
		ostream &out;

		const string EOL = "\r\n";

	public:
		Writer(ostream &out);

		void writeLine(string code);

		void writeTd(int x, int y);
		void writeTf(string fontName, int fontSize);
		void writeTj(string text);
		void writeTm(int, int, int, int, int x, int y);
	};
}
