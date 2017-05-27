#include <iostream>
#include <memory>
#include <sstream>

#include "DocumentModel/Elements/Paragraph.hpp"
#include "DocumentModel/Elements/TextNode.hpp"
#include "ParseError.hpp"
#include "Parser.hpp"

using namespace DocumentModel::Elements;
using namespace DocumentModel;
using namespace Input;
using namespace std;


shared_ptr<Document>
Parser::parseDocument()
{
	shared_ptr<Document> doc(new Document());
	parseChildren(shared_ptr<Element>(doc));

	doc->removeEmptyChildren();

	return doc;
}


void
Parser::parseChildren(shared_ptr<Element> parent)
{
	char c;
	bool escaping = false;

	while (stream.get(c)) {
		if (escaping) {
			if (!isControlChar(c)) {
				throw new ParseError(
					"Invalid escape sequence"
				);
			}
		}
		else {
			if (isControlChar(c)) {
				switch (c) {
				case Parser::EscapeChar:
					escaping = true;
					break;

				case Parser::ElementBegin:
					processTextNode(parent);
					parent->addChild(parseElement(parent));
					break;

				case Parser::ElementEnd:
					stream.unget();
					processTextNode(parent);
					return;
				}

				continue;
			}
		}

		escaping = false;
		textbuf.put(c);
	}

	processTextNode(parent);
}


shared_ptr<Element>
Parser::parseElement(shared_ptr<Element> parent)
{
	string name = parseName();

	/*
	 * some names are reserved and treated differently
	 */
	Element *el;
	if (name == "p") {
		el = new Paragraph(parent, 500); /* TODO */
	}
	else {
		el = new DocumentModel::Elements::Container(parent, name);
	}

	el->name = name;

	shared_ptr<Element> elPtr(el);
	parseChildren(elPtr);

	if (stream.get() != Parser::ElementEnd) {
		throw new ParseError("Parse error: missing }");
	}

	return elPtr;
}


void
Parser::processTextNode(shared_ptr<Element> parent)
{
	if (textbuf.str().size() > 0) {
		shared_ptr<TextNode> node(new TextNode(parent, textbuf.str()));
		parent->addChild(node);

		textbuf.str(string());
		textbuf.clear();
	}
}


string
Parser::parseName()
{
	string name;

	char c;
	while (stream.get(c)) {
		if (isWhiteChar(c)) {
			break;
		}

		if (isControlChar(c)) {
			stream.unget();
			break;
		}

		name += c;
	}

	return name;
}
