#pragma once

#include <istream>
#include <memory>
#include <sstream>

#include "DocumentModel/Document.hpp"

using namespace std;
using namespace DocumentModel;


namespace Input
{
	class Parser
	{
		istream &stream;
		stringstream textbuf;

		Parser();

		void parseChildren(vector<shared_ptr<Element>> &children);
		shared_ptr<Element> parseElement();
		string parseName();
		void pushTextNode(vector<shared_ptr<Element>> &children);

	public:
		static constexpr char ElementBegin = '{';
		static constexpr char ElementEnd = '}';
		static constexpr char EscapeChar = '`';

		static constexpr char ArgSep = ' ';

		Parser(istream &stream);
		unique_ptr<Document> parseDocument();
		static bool isControlChar(char c);
		static bool isWhiteChar(char c);
	};
}
