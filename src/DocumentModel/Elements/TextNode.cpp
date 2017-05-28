#include <iostream>
#include <memory>

#include "BoxModel/Char.hpp"
#include "BoxModel/HGlue.hpp"
#include "BoxModel/Line.hpp"
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
	int dashCount = 0;

	shared_ptr<Style> style = getStyle();


	for (uint i = 0; i < text.length(); i++) {
		if (text[i] != '-') {
			if (dashCount > 0) {
				if (dashCount == 1) { /* regular dash */
					boxes.push_back(shared_ptr<Box>(
						new Char(
							text[i],
							style->getFontFamily(),
							style->getFontSize()
						)
					));
				}
				else if (dashCount == 2) { /* longer dash */
					boxes.push_back(shared_ptr<Box>(
						new Line(
							7,
							0,
							-style->getFontSize() / 2
						)
					));
				}
				else { /* longest dash */

				}

				dashCount = 0;
			}
		}

		if (Parser::isWhiteChar(text[i])) {
			double regularGlueWidth = 0.6 * style->getFontSize();
			if (pushGlue)
				boxes.push_back(shared_ptr<Box>(
					new HGlue(
						0,
						regularGlueWidth,
						0.1 * regularGlueWidth,
						0.6 * regularGlueWidth
					)
				));

			pushGlue = false;
		}
		else {
			if (text[i] == '-') {
				dashCount++;
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
}
