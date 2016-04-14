#pragma once

#include <ostream>


namespace PS
{
	class Writer
	{
		const string EOL = "\r\n";

		void writeLine(string code);
	public:
		Writer(ostream &out);

		void writeTf(string fontName, int fontSize);
		void writeTj(string text);
		void writeTm(int, int, int, int, int x, int y);
	};
}
