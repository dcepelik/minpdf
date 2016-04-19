#include <iostream>
#include <memory>
#include <regex>

#include "BoxModel/Char.hpp"
#include "BoxModel/HorizontalGlue.hpp"
#include "Element.hpp"
#include "Input/Parser.hpp"
#include "TextNode.hpp"


using namespace BoxModel;
using namespace DocumentModel::Elements;
using namespace Input;
using namespace std;


TextNode::TextNode(string text) : Element("text")
{
	this->text = text;
}


void
TextNode::render(vector<shared_ptr<Box>> &boxes)
{
	bool pushGlue = false;

	for (uint i = 0; i < text.length(); i++) {
		if (Parser::isWhiteChar(text[i])) {
			if (pushGlue)
				boxes.push_back(shared_ptr<Box>(new HorizontalGlue()));

			pushGlue = false;
		}
		else {
			boxes.push_back(shared_ptr<Box>(new Char(text[i])));
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
