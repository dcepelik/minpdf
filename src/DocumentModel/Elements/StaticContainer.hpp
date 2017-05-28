#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "Container.hpp"

using namespace BoxModel;
using namespace DocumentModel;
using namespace DocumentModel::Elements;
using namespace std;


namespace DocumentModel
{
	namespace Elements
	{
		class StaticContainer : public Container
		{
		protected:
			vector<shared_ptr<Box>> boxes;


		public:
			StaticContainer(shared_ptr<Element> parent)
				: Container(parent, "static-container")
			{
			}


			void addBox(shared_ptr<Box> box)
			{
				boxes.push_back(box);
			}


			void render(vector<shared_ptr<Box>> &boxes)
			{
				for (auto box: this->boxes)
					boxes.push_back(box);
			}
		};
	}
}
