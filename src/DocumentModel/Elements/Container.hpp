#pragma once

#include <memory>
#include <vector>

#include "BoxModel/Box.hpp"
#include "DocumentModel/Elements/Element.hpp"

using namespace BoxModel;
using namespace DocumentModel::Elements;
using namespace std;


namespace DocumentModel
{
	namespace Elements
	{
		class Container : public Element
		{
			string name;

		public:
			vector<shared_ptr<Element>> children;

			Container(string name);
			void expand(vector<shared_ptr<Box>> &boxes);
			virtual void dump(int level = 0);
			virtual void removeEmptyChildren();
			virtual bool empty();
		};
	}
}
