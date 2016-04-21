#include <iostream>
#include <memory>
#include <regex>

#include "BoxModel/Char.hpp"
#include "BoxModel/HGlue.hpp"
#include "Element.hpp"
#include "Input/Parser.hpp"
#include "Styles/StyleTable.hpp"
#include "TextNode.hpp"


using namespace BoxModel;
using namespace DocumentModel::Elements;
using namespace DocumentModel;
using namespace Input;

using namespace std;


TextNode::TextNode(shared_ptr<Element> parent, string text) : Element(parent, "text")
{
	this->text = text;
}


void
TextNode::render(vector<shared_ptr<Box>> &boxes)
{
	bool pushGlue = false;

	shared_ptr<Style> style = getDocument()->getStyleTable()->getStyle("p");

	for (uint i = 0; i < text.length(); i++) {
		if (Parser::isWhiteChar(text[i])) {
			int regularGlueWidth = 0.8 * style->fontSize;
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
					style->fontFamily,
					style->fontSize
				)
			);

			boxes.push_back(charBox);
			pushGlue = true;
		}
	}
}


void
TextNode::dump(int level)
{
	string replaced;
	replaced = regex_replace(text, regex("\\n"), "\\n");
	replaced = regex_replace(replaced, regex("\\t"), "\\t");

	cout << string(level, '\t') << "\"" << replaced << "\"" << endl;
}


bool
TextNode::empty()
{
	for (uint i = 0; i < text.length(); i++) {
		if (!Parser::isWhiteChar(text[i])) {
			return false;
		}
	}

	return true;
}
