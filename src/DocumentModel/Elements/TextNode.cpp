#include <iostream>
#include <memory>

#include "BoxModel/Char.hpp"
#include "BoxModel/HGlue.hpp"
#include "Element.hpp"
#include "Styles/StyleTable.hpp"
#include "TextNode.hpp"

using namespace BoxModel;
using namespace DocumentModel::Elements;
using namespace DocumentModel;

using namespace std;


void
TextNode::render(vector<shared_ptr<Box>> &boxes)
{
	bool pushGlue = true;

	shared_ptr<Style> style = getStyle();
	cout << this->name << endl;

	for (uint i = 0; i < text.length(); i++) {
		if (Parser::isWhiteChar(text[i])) {
			double regularGlueWidth = 0.8 * style->getFontSize();
			if (pushGlue)
				boxes.push_back(shared_ptr<Box>(
					new HGlue(
						0,
						regularGlueWidth,
						0.3 * regularGlueWidth,
						0.6 * regularGlueWidth
					)
				));

			pushGlue = false;
		}
		else {
			shared_ptr<Box> charBox(
				new Char(
					text[i],
					style->getFontFamily(),
					style->getFontSize()
				)
			);

			boxes.push_back(charBox);
			pushGlue = true;
		}
	}
}
