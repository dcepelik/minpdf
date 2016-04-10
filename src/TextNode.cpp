#include <iostream>
#include <regex>

#include "Char.hpp"
#include "Element.hpp"
#include "HorizontalGlue.hpp"
#include "Parser.hpp"
#include "TextNode.hpp"


using namespace std;


TextNode::TextNode(string text) : Element("text")
{
	this->text = text;
}


void
TextNode::expand(vector<shared_ptr<Box>> &boxes)
{
	for (uint i = 0; i < text.length(); i++) {
		if (Parser::isWhiteChar(text[i])) {
			boxes.push_back(shared_ptr<Box>(new HorizontalGlue()));
		}
		else {
			boxes.push_back(shared_ptr<Box>(new Char(text[i])));
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
