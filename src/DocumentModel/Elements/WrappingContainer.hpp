#pragma once

#include "BoxModel/Box.hpp"
#include "BoxModel/Glue.hpp"
#include "BoxModel/List.hpp"
#include "Container.hpp"

using namespace BoxModel;


namespace DocumentModel
{
	namespace Elements
	{
		class WrappingContainer : public Container
		{
		protected:
			int maxSize;

			virtual double getBoxSize(shared_ptr<Box> box) = 0;
			virtual shared_ptr<Glue> createNewInfGlue() = 0;
			virtual shared_ptr<List> createNewList(
				vector<shared_ptr<Box>>::iterator begin,
				vector<shared_ptr<Box>>::iterator end
			) = 0;
			virtual shared_ptr<Glue> createNewInterlineGlue() = 0;

		public:
			WrappingContainer(shared_ptr<Element> parent,
				string name, int maxSize)
				: Container(parent, name)
			{
				this->maxSize = maxSize;
			}


			void render(vector<shared_ptr<Box>> &boxes);
		};
	}
}
