#pragma once

#include <string>
#include <regex>

#include "BoxModel/Box.hpp"
#include "Element.hpp"
#include "Input/Parser.hpp"

using namespace BoxModel;
using namespace Input;
using namespace std;


namespace DocumentModel
{
	namespace Elements
	{
		class TextNode : public Element
		{
			string text;

		public:
			TextNode(shared_ptr<Element> parent, string text)
				: Element(parent, "text")
			{
				this->text = text;
			}


			virtual void render(vector<shared_ptr<Box>> &boxes);


			void dump(int level)
			{
				string replaced;
				replaced = regex_replace(text, regex("\\n"), "\\n");
				replaced = regex_replace(replaced, regex("\\t"), "\\t");

				cout << string(level, '\t') << "\"" << replaced
					<< "\"" << endl;
			}


			double getNaturalWidth()
			{
				vector<shared_ptr<Box>> boxes;
				double width = 0;

				this->render(boxes);

				for (auto box: boxes)
					width += box->getNaturalWidth();

				return width;
			}


			string getTextualContent()
			{
				return text;
			}


			bool empty()
			{
				for (uint i = 0; i < text.length(); i++) {
					if (!Parser::isWhiteChar(text[i])) {
						return false;
					}
				}

				return true;
			}
		};
	}
}
