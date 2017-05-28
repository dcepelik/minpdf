#pragma once

#include "../Element.hpp"
#include <memory>

using namespace std;

namespace DocumentModel
{
	namespace Elements
	{
		namespace Commands
		{
			class Command : public Element
			{
			public:
				Command(shared_ptr<Element> parent, string name)
					: Element(parent, name)
				{
				}
			};
		}
	}
}
