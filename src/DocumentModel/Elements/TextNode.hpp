#pragma once

#include <string>

#include "BoxModel/Box.hpp"
#include "Element.hpp"

using namespace BoxModel;
using namespace std;


namespace DocumentModel
{
	namespace Elements
	{
		class TextNode : public Element
		{
			string text;

		public:
			TextNode(shared_ptr<Element> parent, string text);

			virtual void render(vector<shared_ptr<Box>> &boxes);
			virtual void dump(int level = 0);
			virtual bool empty();
		};
	}
}
