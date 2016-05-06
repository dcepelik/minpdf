#pragma once

#include <istream>
#include <memory>
#include <sstream>

#include "DocumentModel/Document.hpp"
#include "DocumentModel/Elements/Element.hpp"

using namespace DocumentModel;
using namespace DocumentModel::Elements;
using namespace std;


namespace Input
{
	class Parser
	{
		istream &stream;
		stringstream textbuf;

		Parser();

		void parseChildren(shared_ptr<Element> parent);
		shared_ptr<Element> parseElement(shared_ptr<Element> parent);
		string parseName();
		void processTextNode(shared_ptr<Element> parent);


	public:
		static constexpr char ElementBegin = '{';
		static constexpr char ElementEnd = '}';
		static constexpr char EscapeChar = '`';
		static constexpr char ArgSep = ' ';


		static bool isControlChar(char c)
		{
			return c == Parser::EscapeChar
				|| c == Parser::ElementBegin
				|| c == Parser::ElementEnd;
		}


		static bool isWhiteChar(char c)
		{
			return c == '\t'
				|| c == '\r'
				|| c == '\n'
				|| c == ' ';
		}


		Parser(istream &stream) : stream(stream)
		{
			textbuf = stringstream();
		}


		shared_ptr<Document> parseDocument();
	};
}
