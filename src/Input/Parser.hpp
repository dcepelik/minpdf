#pragma once

#include <istream>
#include <memory>
#include <sstream>

#include "DocumentModel/Document.hpp"
#include "DocumentModel/Elements/Element.hpp"

namespace DM = DocumentModel;
using namespace DM::Elements;
using namespace std;


namespace Input
{
	class Parser
	{
		istream &stream;
		stringstream textbuf;
		string filename;

		Parser();

		void parseChildren(shared_ptr<Element> parent);
		shared_ptr<Element> parseElement(shared_ptr<Element> parent);
		shared_ptr<Element> parseCommand(shared_ptr<Element> parent);
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


		Parser(istream &stream, string filename) : stream(stream)
		{
			textbuf = stringstream();
			this->filename = filename;
		}


		shared_ptr<DM::Document> parseDocument();
	};
}
