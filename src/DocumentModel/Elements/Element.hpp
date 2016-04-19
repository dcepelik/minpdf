#pragma once

#include <memory>
#include <string>
#include <vector>

#include "BoxModel/Box.hpp"

using namespace BoxModel;
using namespace std;


namespace DocumentModel
{
	namespace Elements
	{
		class Element
		{
			string name;
			Element();

		public:
			Element(string name);

			virtual void addChild(shared_ptr<Element> child);

			virtual void render(vector<shared_ptr<Box>> &boxes);
			virtual void dump(int level = 0);
			virtual void removeEmptyChildren();
			virtual bool empty();
		};
	}
}
