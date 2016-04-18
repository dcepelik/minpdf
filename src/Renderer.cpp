#include <sstream>
#include <algorithm>

#include "Renderer.hpp"
#include "BoxModel/Char.hpp"
#include "BoxModel/HorizontalGlue.hpp"
#include "BoxModel/LineBreak.hpp"

using namespace std;
using namespace BoxModel;


Renderer::Renderer()
{

}


void
Renderer::render(vector<shared_ptr<Box>> &boxes)
{
	int maxLineWidth = 612;

	auto initGlueIterator = boxes.insert(
		boxes.begin(),
		shared_ptr<Box>(new HorizontalGlue())
	);
	(*initGlueIterator)->setBadness(0);

	shared_ptr<Box> lastBreak;
	for (auto l = boxes.begin(); l != boxes.end(); l++) {
		if ((*l)->getType() != HorizontalGlueBox)
			continue;

		int width = 0;

		for (auto r = l + 1; r < boxes.end(); r++) {
			width += (*r)->getWidth();

			if ((*r)->getType() != HorizontalGlueBox)
				continue;

			int badness = (maxLineWidth - width)
				* (maxLineWidth - width);

			/* relax the edge */
			if ((*r)->getBadness() > (*l)->getBadness() + badness) {
				(*r)->setBadness((*l)->getBadness() + badness);
				(*r)->setPrev(*l);

				lastBreak = (*l);
			}
		}
	}

	while (lastBreak.get() != NULL) {
		if (lastBreak != *boxes.begin()) {
			replace(boxes.begin(), boxes.end(), lastBreak,
				shared_ptr<Box>(new LineBreak()));
		}
		lastBreak = lastBreak->getPrev();
	}

	auto lastEnd = boxes.begin();

	boxes.erase(initGlueIterator);

	int count = 0;
	int width = 0;

	for (auto r = boxes.begin(); r != boxes.end(); r++) {
		if ((*r)->getType() == HorizontalGlueBox) {
			count++;
		}
		else {
			width += (*r)->getWidth();

			if ((*r)->getType() != LineBreakBox)
				continue;

			int avg = 0;
			if (count > 0)
				avg = (maxLineWidth - width) / count;

			for (auto l = lastEnd; l != r; l++)
				if ((*l)->getType() == HorizontalGlueBox)
					(*l)->setWidth(avg);

			lastEnd = r;
			count = width = 0;
		}
	}
}
