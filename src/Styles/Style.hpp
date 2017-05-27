#pragma once

#include <string>
#include <memory>

using namespace std;

namespace Styles
{
	struct Style
	{
		bool fontFamilyValid;
		bool fontSizeValid;

		string fontFamily;
		int fontSize;


		void patch(Style *patchStyle)
		{
			if (!fontFamilyValid)
				fontFamily = patchStyle->fontFamily;

			if (!fontSizeValid)
				fontSize = patchStyle->fontSize;
		}
	};
}
