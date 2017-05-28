#pragma once

#include "Command.hpp"
#include "../TextNode.hpp"
#include "../Element.hpp"


namespace DocumentModel
{
	namespace Elements
	{
		namespace Commands
		{
			class FilenameCommand : public Command
			{
			public:
				FilenameCommand(shared_ptr<Element> parent)
					: Command(parent, "!filename")
				{
				}

				virtual void render(vector<shared_ptr<Box>> &boxes)
				{
					(void) boxes;
					TextNode tn(shared_ptr<Element>(this), getDocument()->getFilename());
					tn.render(boxes);
				}


				virtual void dump(int level)
				{
					string tabs(level, '\t');
					cout << tabs << "Command [" << name << "]" << endl;
				}
			};
		}
	}
}
