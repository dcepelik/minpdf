#include <cassert>
#include <cmath>
#include <stack>

#include "Paragraph.hpp"
#include "BoxModel/HorizontalGlue.hpp"
#include "BoxModel/HList.hpp"

using namespace DocumentModel::Elements;


Paragraph::Paragraph() : Container("p")
{
}


void
Paragraph::render(vector<shared_ptr<Box>> &boxes)
{
	int maxLineWidth = 612;

	vector<shared_ptr<Box>> innerBoxes;

	/*
	 * addition of initial glue simplifies the algorithm,
	 * glue0 will be removed later
	 */
	Box *glue0 = new HorizontalGlue();
	glue0->setBadness(0);

	innerBoxes.push_back(shared_ptr<Box>(glue0));
	Container::render(innerBoxes);

	/*
	 * add infinitely stretchable glue to the end of the paragraph
	 */
	innerBoxes.push_back(shared_ptr<Box>(new HorizontalGlue()));

	shared_ptr<Box> lastBreak;
	for (auto l = innerBoxes.begin(); l != innerBoxes.end(); l++) {
		auto start = (*l);

		int width = 0;
		if (start->getType() != HorizontalGlueBox)
			continue;

		for (auto r = l + 1; r < innerBoxes.end(); r++) {
			auto end = (*r);

			width += end->getWidth();

			if (end->getType() != HorizontalGlueBox)
				continue;

			int badness = (maxLineWidth - width) * (maxLineWidth - width);
			int newBadness = start->getBadness() + badness;

			if (end->getBadness() > newBadness) {
				end->setBadness(newBadness);
				end->setPrev(start);

				lastBreak = end;
			}
		}
	}

	stack<shared_ptr<Box>> lineBreaks;

	auto lineBreak = lastBreak;
	while (lineBreak.get() != NULL) {
		lineBreaks.push(lineBreak);
		lineBreak = lineBreak->getPrev();
	}

	lineBreaks.pop();
	innerBoxes.erase(innerBoxes.begin()); /* remove glue0 */

	shared_ptr<HList> row(new HList());
	for (auto it = innerBoxes.begin(); it < innerBoxes.end(); it++) {
		
		if (*it == lineBreaks.top()) {
			cout << "Popped" << endl;
			lineBreaks.pop();

			boxes.push_back(row);
			row = shared_ptr<HList>(new HList());
		}
		else {
			row->addItem(*it);
		}
	}
}
