#pragma once

#include "Command.hpp"
#include "BoxModel/Line.hpp"
#include "DocumentModel/Document.hpp"

using namespace BoxModel;


namespace DocumentModel
{
	namespace Elements
	{
		namespace Commands
		{
			class LineCommand : public Command
			{
			public:
				LineCommand(shared_ptr<Element> parent)
					: Command(parent, "!line")
				{
				}

				virtual void render(vector<shared_ptr<Box>> &boxes)
				{
					boxes.push_back(shared_ptr<Box>(new Line(getDocument()->getContentWidth(), 0, 0, true)));
				}
			};
		}
	}
}
