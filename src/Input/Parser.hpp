#pragma once

#include <istream>
#include <memory>
#include <sstream>

#include "DocumentModel/Document.hpp"

using namespace DocumentModel;
using namespace std;


namespace Input
{
	class Parser
	{
		istream &stream;
		stringstream textbuf;

		Parser();

		void parseChildren(shared_ptr<Element> parent);
		shared_ptr<Element> parseElement();
		string parseName();
		void processTextNode(shared_ptr<Element> parent);

	public:
		static constexpr char ElementBegin = '{';
		static constexpr char ElementEnd = '}';
		static constexpr char EscapeChar = '`';

		static constexpr char ArgSep = ' ';

		Parser(istream &stream);
		shared_ptr<Document> parseDocument();
		static bool isControlChar(char c);
		static bool isWhiteChar(char c);
	};
}
