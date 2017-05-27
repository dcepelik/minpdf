#pragma once

#include "WrappingContainer.hpp"
#include "BoxModel/HGlue.hpp"
#include "BoxModel/VGlue.hpp"
#include "BoxModel/HList.hpp"


namespace DocumentModel
{
	namespace Elements
	{
		class HWrappingContainer : public WrappingContainer
		{
		protected:
			double getBoxSize(shared_ptr<Box> box)
			{
				return box->getWidth();
			}


			shared_ptr<Glue> createNewInfGlue()
			{
				return shared_ptr<Glue>(new HGlue(1, 0, 0, 0));
			}


			shared_ptr<Glue> createNewInterlineGlue()
			{
				return shared_ptr<Glue>(new VGlue(0, 3, 0, 0));
			}


			shared_ptr<List>
			createNewList(vector<shared_ptr<Box>>::iterator begin,
				vector<shared_ptr<Box>>::iterator end)
			{
				HList *list = new HList(maxSize);

				for (auto it = begin; it != end; it++)
					list->addChild(*it);

				return shared_ptr<List>(list);
			}

		public:
			HWrappingContainer(shared_ptr<Element> parent,
				string name, int width)
				: WrappingContainer(parent, name, width)
			{
			};
		};
	}
}
