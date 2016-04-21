#pragma once

#include <memory>
#include <string>
#include <vector>

#include "BoxModel/Box.hpp"

using namespace BoxModel;
using namespace Styles;
using namespace std;


namespace DocumentModel
{
	class Document;

	namespace Elements
	{
		class Element
		{
		protected:
			string name;
			shared_ptr<Element> parent;

			Element();

		public:
			Element(shared_ptr<Element> parent, string name);

			shared_ptr<Element> getParent();
			Document *getDocument();

			/* TODO remove this, create containers instead! */
			virtual void addChild(shared_ptr<Element> child);

			virtual void render(vector<shared_ptr<Box>> &boxes);
			virtual void dump(int level = 0);
			virtual void removeEmptyChildren();
			virtual bool empty();
		};
	}
}
