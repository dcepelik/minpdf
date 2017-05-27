#pragma once

#include "WrappingContainer.hpp"
#include "BoxModel/HGlue.hpp"
#include "BoxModel/VGlue.hpp"
#include "BoxModel/VList.hpp"


namespace DocumentModel
{
	namespace Elements
	{
		class VWrappingContainer : public WrappingContainer
		{
		protected:
			double getBoxSize(shared_ptr<Box> box)
			{
				return box->getHeight();
			}


			shared_ptr<Glue> createNewInfGlue()
			{
				return shared_ptr<Glue>(new VGlue(1, 0, 0, 0));
			}


			shared_ptr<List> createNewList(
				vector<shared_ptr<Box>>::iterator begin,
				vector<shared_ptr<Box>>::iterator end
			) {
				VList *list = new VList(maxSize);

				for (auto it = begin; it != end; it++)
					list->addChild(*it);

				return shared_ptr<List>(list);
			}


			shared_ptr<Glue> createNewInterlineGlue()
			{
				return shared_ptr<Glue>(new VGlue(0, 0, 0, 0));
			}

		public:
			VWrappingContainer(shared_ptr<Element> parent,
				string name, int width)
				: WrappingContainer(parent, name, width)
			{
			};

		};
	}
}
