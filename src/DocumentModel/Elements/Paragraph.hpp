#pragma once

#include <string>
#include "Container.hpp"

using namespace BoxModel;
using namespace DocumentModel;
using namespace std;


namespace DocumentModel
{
	namespace Elements
	{
		class Paragraph : public Container
		{
		public:
			Paragraph(shared_ptr<Element> parent);

			virtual void render(vector<shared_ptr<Box>> &boxes)
				override;
		};
	}
}
