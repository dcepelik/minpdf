#pragma once

#include <memory>
#include "Container.hpp"

using namespace DocumentModel;
using namespace std;


namespace DocumentModel
{
	namespace Elements
	{
		enum ItemListStyle
		{
			ItemListStyleUnordered,
			ItemListStyleNumbered,
			ItemListStyleRoman,
		};

		class ItemList : public Container
		{
			ItemListStyle style;

		public:
			ItemList(shared_ptr<Element> parent, ItemListStyle style) : Container(parent, "item-list")
			{
				this->style = style;
			}


			void render(vector<shared_ptr<Box>> &boxes);
		};
	}
}
