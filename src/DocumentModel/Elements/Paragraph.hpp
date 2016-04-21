#pragma once

#include <string>
#include "HWrappingContainer.hpp"

using namespace DocumentModel;
using namespace std;


namespace DocumentModel
{
	namespace Elements
	{
		class Paragraph : public HWrappingContainer
		{
		public:
			Paragraph(shared_ptr<Element> parent, int width);
		};
	}
}
