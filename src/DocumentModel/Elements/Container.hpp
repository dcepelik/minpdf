#pragma once

#include <memory>
#include <vector>

#include "BoxModel/Box.hpp"
#include "Element.hpp"

using namespace BoxModel;
using namespace std;


namespace DocumentModel
{
	namespace Elements
	{
		class Container : public Element
		{
			string name;
			vector<shared_ptr<Element>> children;

		public:
			Container(string name);

			void addChild(shared_ptr<Element> child);

			void expand(vector<shared_ptr<Box>> &boxes);
			virtual void dump(int level = 0);
			virtual void removeEmptyChildren();
			virtual bool empty();
		};
	}
}
