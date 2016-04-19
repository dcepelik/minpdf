#pragma once

#include <string>
#include "Container.hpp"


namespace DocumentModel
{
	namespace Elements
	{
		class Paragraph : public Container
		{
		public:
			Paragraph();

			virtual void render(vector<shared_ptr<Box>> &boxes)
				override;
		};
	}
}
