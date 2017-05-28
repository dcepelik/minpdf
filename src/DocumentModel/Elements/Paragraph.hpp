#pragma once

#include <string>
#include "HWrappingContainer.hpp"
#include "BoxModel/VGlue.hpp"

using namespace DocumentModel;
using namespace std;


namespace DocumentModel
{
	namespace Elements
	{
		class Paragraph : public HWrappingContainer
		{
		public:
			Paragraph(shared_ptr<Element> parent, int width)
				: HWrappingContainer(parent, "p", width)
			{
			}


			void postrender(vector<shared_ptr<Box>> &boxes)
			{
				(void) boxes;
				//VGlue *parindent = new VGlue(0, 5, 0, 0);
				//boxes.push_back(shared_ptr<Box>(parindent));
			}
		};
	}
}
