#pragma once

#include <string>
#include <memory>

using namespace std;

namespace Styles
{
	struct Style
	{
	private:
		bool fontFamilyValid = false;
		bool fontSizeValid = false;

		string fontFamily;
		int fontSize;


	public:
		void setFontFamily(string fontFamily)
		{
			this->fontFamily = fontFamily;
			this->fontFamilyValid = true;
		}


		void setFontSize(int fontSize)
		{
			this->fontSize = fontSize;
			this->fontSizeValid = true;
		}


		string getFontFamily()
		{
			return fontFamily;
		}


		int getFontSize()
		{
			return fontSize;
		}


		void patch(Style *patchStyle)
		{
			if (patchStyle->fontFamilyValid)
				setFontFamily(patchStyle->fontFamily);

			if (patchStyle->fontSizeValid)
				setFontSize(patchStyle->fontSize);
		}
	};
}
