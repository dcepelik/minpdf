#include <cassert>
#include <cmath>
#include <stack>

#include "Paragraph.hpp"
#include "BoxModel/HGlue.hpp"
#include "BoxModel/HList.hpp"

using namespace BoxModel;
using namespace DocumentModel;
using namespace DocumentModel::Elements;


Paragraph::Paragraph(shared_ptr<Element> parent) : Container(parent, "p")
{
}


void
Paragraph::render(vector<shared_ptr<Box>> &boxes)
{
	int maxLineWidth = 500;

	vector<shared_ptr<Box>> innerBoxes;

	/*
	 * addition of initial glue simplifies the algorithm,
	 * glue0 will be removed later
	 */
	Box *glue0 = new HGlue(0, 0, 0, 0);
	glue0->setBadness(0);

	innerBoxes.push_back(shared_ptr<Box>(glue0));
	Container::render(innerBoxes);

	/*
	 * add infinitely stretchable glue to the end of the paragraph
	 */
	innerBoxes.push_back(shared_ptr<Box>(new HGlue(1, 0, 0, 0)));

	shared_ptr<Box> lastBreak;

	for (auto l = innerBoxes.begin(); l != innerBoxes.end(); l++) {
		auto start = (*l);

		int width = 0;

		int maxSpace = 0;
		int minSpace = 0;
		int regularSpace = 0;

		if (!dynamic_cast<Glue *>(start.get()))
			continue;

		for (auto r = l + 1; r != innerBoxes.end(); r++) {
			auto end = (*r);

			Glue *g;
			if ((g = dynamic_cast<Glue *>(end.get()))) {
				maxSpace += g->getMaxSize();
				minSpace += g->getMinSize();
				regularSpace += g->getSize();
			}
			else {
				width += end->getWidth();
			}

			if (width + minSpace > maxLineWidth)
				break; /* overfull line */

			if (!dynamic_cast<Glue *>(end.get()))
				continue;

			int requiredSpace = maxLineWidth - width;

			int badness = 0;
			if (1 || requiredSpace > maxSpace) {
				badness = 100 * pow((float)requiredSpace / maxSpace, 3);
			}
			else if (requiredSpace < minSpace) {
				badness = 100 * pow((float)minSpace / requiredSpace, 3);
			}

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

	shared_ptr<HList> row(new HList(500)), lastRow;
	row->addChild(shared_ptr<Box>(new HGlue(0, 40, 0, 0)));
	for (auto it = innerBoxes.begin(); it < innerBoxes.end(); it++) {
		if (*it == lineBreaks.top()) {
			lineBreaks.pop();

			boxes.push_back(row);
			row = shared_ptr<HList>(new HList(500));
		}
		else {
			row->addChild(*it);
			lastRow = row;
		}
	}

	lastRow->addChild(shared_ptr<Box>(new HGlue(1, 0, 0, 0)));
}
