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
			shared_ptr<Element> parent;

			Element();

		public:
			string name;

			Element(shared_ptr<Element> parent, string name)
			{
				this->parent = parent;
				this->name = name;
			}


			virtual void addChild(shared_ptr<Element> child)
			{
				/* TODO remove this method, create containers instead! */
				(void)child;
				throw new domain_error("Cannot add children to non-containers");
			}


			Element *getParent()
			{
				return parent.get();
			}


			virtual void render(vector<shared_ptr<Box>> &boxes)
			{
				/* by default, element will not produce any boxes */
				(void)boxes;
			}


			virtual void removeEmptyChildren()
			{
				/* element has no children */
			}


			virtual bool empty()
			{
				return false;
			}


			virtual void dump(int level)
			{
				string tabs(level, '\t');
				cout << tabs << "Element [" << name << "]:" << endl;
			}

			Document *getDocument();
			unique_ptr<Style> getStyle();
		};
	}
}
