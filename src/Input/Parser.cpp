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


bool
Parser::isControlChar(char c)
{
	return c == Parser::EscapeChar
		|| c == Parser::ElementBegin
		|| c == Parser::ElementEnd;
}


bool
Parser::isWhiteChar(char c)
{
	return c == '\t'
		|| c == '\r'
		|| c == '\n'
		|| c == ' ';
}


Parser::Parser(istream &stream) : stream(stream)
{
	textbuf = stringstream();
}


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
					parent->addChild(parseElement());
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
Parser::parseElement()
{
	string name = parseName();

	shared_ptr<Container> container(new Container(name));
	parseChildren(container);

	if (stream.get() != Parser::ElementEnd) {
		throw new ParseError("Parse error: missing " + Parser::ElementEnd);
	}

	return container;
}


void
Parser::processTextNode(shared_ptr<Element> parent)
{
	if (textbuf.str().size() > 0) {
		shared_ptr<TextNode> node(new TextNode(textbuf.str()));
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
