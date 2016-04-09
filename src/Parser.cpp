#include <memory>
#include <iostream>
#include <sstream>

#include "Parser.hpp"
#include "Paragraph.hpp"
#include "TextNode.hpp"

using namespace std;


Parser::Parser(istream &stream) : stream(stream)
{
	textbuf = stringstream();
}


unique_ptr<Document>
Parser::parseDocument()
{
	vector<shared_ptr<Element>> elems;

	Document *doc = new Document();
	parseChildren(doc->children);

	doc->removeEmptyChildren();
	doc->dump();

	return unique_ptr<Document>(doc);
}


void
Parser::parseChildren(vector<shared_ptr<Element>> &children)
{
	char c;
	bool escaping = false;
	while (stream.get(c)) {
		if (escaping) {
			if (!isControlChar(c)) {
				cerr << "Cannot escape '" << c << "'" << endl;
			}
		}
		else {
			if (isControlChar(c)) {
				switch (c) {
				case Parser::EscapeChar:
					escaping = true;
					break;

				case Parser::ElementBegin:
					pushTextNode(children);
					stream.unget();
					children.push_back(parseElement());
					break;

				case Parser::ElementEnd:
					stream.unget();
					pushTextNode(children);
					return;
				}

				continue;
			}
		}

		escaping = false;
		textbuf.put(c);
	}

	pushTextNode(children);
}


void
Parser::pushTextNode(vector<shared_ptr<Element>> &children)
{
	if (textbuf.str().size() > 0) {
		children.push_back(shared_ptr<Element>(
			new TextNode(textbuf.str())
		));

		/* clear the buffer */
		textbuf.str(string());
	}
}


shared_ptr<Element>
Parser::parseElement()
{
	if (stream.get() != Parser::ElementBegin) {
		cerr << "Parse error: missing " << Parser::ElementBegin << endl;
	}

	string name = parseName();

	Container *cont = new Container(name);
	parseChildren(cont->children);

	if (stream.get() != Parser::ElementEnd) {
		cerr << "Parse error: mssing " << Parser::ElementEnd << endl;
	}

	return shared_ptr<Element>(cont);
}


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


string
Parser::parseName()
{
	string name;

	char c;
	while (stream.get(c)) {
		if (isWhiteChar(c))
			break;

		if (isControlChar(c)) {
			stream.unget();
			break;
		}

		name += c;
	}

	return name;
}
