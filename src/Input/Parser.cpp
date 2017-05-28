#include <iostream>
#include <memory>
#include <sstream>

#include "DocumentModel/Elements/Paragraph.hpp"
#include "DocumentModel/Elements/TextNode.hpp"
#include "DocumentModel/Elements/ItemList.hpp"
#include "DocumentModel/Elements/Commands/FilenameCommand.hpp"
#include "DocumentModel/Elements/Commands/LineCommand.hpp"
#include "ParseError.hpp"
#include "Parser.hpp"

using namespace DocumentModel::Elements::Commands;
using namespace Input;
using namespace std;


shared_ptr<DM::Document>
Parser::parseDocument()
{
	shared_ptr<DM::Document> doc(new DM::Document());
	parseChildren(shared_ptr<Element>(doc));

	doc->removeEmptyChildren();
	doc->setFilename(filename);

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
		else if (isControlChar(c)) {
			switch (c) {
			case Parser::EscapeChar:
				escaping = true;
				break;

			case Parser::ElementBegin:
				stream.get(c);
				if (c != '!') {
					stream.unget();
					processTextNode(parent);
					parent->addChild(parseElement(parent));
				}
				else {
					parent->addChild(parseCommand(parent));
				}
				break;

			case Parser::ElementEnd:
				stream.unget();
				processTextNode(parent);
				return;
			}

			continue;
		}

		escaping = false;
		textbuf.put(c);
	}

	processTextNode(parent);
}



shared_ptr<Element>
Parser::parseCommand(shared_ptr<Element> parent)
{
	char c;

	(void) parent;
	string name = parseName();

	stream.get(c);
	if (c != Parser::ElementEnd) {
		throw new ParseError("Parse error: missing } after command name");
	}

	if (name == "filename") {
		return shared_ptr<Element>(new FilenameCommand(parent));
	}
	else if (name == "line") {
		return shared_ptr<Element>(new LineCommand(parent));
	}
	else {
		throw new ParseError("Parse error: unknown command");
	}
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
		el = new Paragraph(parent, 400); /* TODO */
	}
	else if (name == "list") {
		el = new ItemList(parent);
	}
	else {
		el = new DM::Elements::Container(parent, name);
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
