#pragma once

#include "WrappingContainer.hpp"


namespace DocumentModel
{
	namespace Elements
	{
		class HWrappingContainer : public WrappingContainer
		{
		protected:
			int getBoxSize(shared_ptr<Box> box);
			shared_ptr<Glue> createNewInfGlue();
			shared_ptr<List> createNewList(
				vector<shared_ptr<Box>>::iterator begin,
				vector<shared_ptr<Box>>::iterator end
			);
			shared_ptr<Glue> createNewInterlineGlue();

		public:
			HWrappingContainer(shared_ptr<Element> parent,
				string name, int width);
		};
	}
}
