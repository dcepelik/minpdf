#pragma once

#include <memory>
#include "Container.hpp"

using namespace DocumentModel;
using namespace std;


namespace DocumentModel
{
	namespace Elements
	{
		class ItemList : public Container
		{
		public:
			ItemList(shared_ptr<Element> parent) : Container(parent, "item-list")
			{
			}


			void render(vector<shared_ptr<Box>> &boxes);
		};
	}
}
