#include <iostream>
#include <regex>

#include "Element.hpp"
#include "TextNode.hpp"
#include "Parser.hpp"


using namespace std;


TextNode::TextNode(string text) : Element("text")
{
	this->text = text;
}


void
TextNode::dump(int level)
{
	string replaced;
	replaced = regex_replace(text, regex("\\n"), "\\n");

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
