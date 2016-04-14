#pragma once

#include <sstream>


namespace PS
{
	class LineState
	{
		int maxWidth;
		int lineWidth = 0;

	public:
		HCanvas(int maxWidth);

		void newLine();

		int getLineWidth();
		int getMaxLineWidth();
		int getFreeSpace();
		bool hasFreeSpace(int space);

		int getBadness();

		int adjustCursor(int value);
	};
}
