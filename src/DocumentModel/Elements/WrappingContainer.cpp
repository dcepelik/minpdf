#include <list>
#include <cmath>

#include "BoxModel/List.hpp"
#include "BoxModel/HGlue.hpp"
#include "WrappingContainer.hpp"

using namespace DocumentModel::Elements;


void
WrappingContainer::render(vector<shared_ptr<Box>> &boxes)
{
	vector<shared_ptr<Box>> inner;

	/*
	 * glue0 and glueE are added in order to simplify the algorithm,
	 * but are useless otherwise and will not be rendered at all
	 *
	 * TODO new HGlue(...) ~~> createNewGlue()
	 */
	Glue *glue0 = new HGlue(0, 0, 0, 0), *glueE = new HGlue(1, 0, 0, 0);
	glue0->setBadness(0);
	inner.push_back(shared_ptr<Box>(glue0));

	DocumentModel::Elements::Container::render(inner);
	inner.push_back(shared_ptr<Box>(glueE));


	/*
	 * the list division algorithm itself
	 */
	for (auto itBegin = inner.begin(); itBegin != inner.end(); itBegin++) {
		auto begin = (*itBegin);

		if (!dynamic_cast<Glue *>(begin.get()))
			continue;

		double sizeOfBoxes = 0;	/* current list size */
		int listBadness;		/* current list badness */
		int newBadness;			/* new badness (when dividing here) */

		double glueSize = 0;	/* regular glue size */
		double minGlueSize = 0;	/* glue size accounting for shrink */
		double maxGlueSize = 0;	/* glue size accounting for stretch */
		double actualGlueSize;	/* actual glue size (as rendered) */
		double naturalSize;		/* natural size of the line */

		for (auto itEnd = itBegin + 1; itEnd != inner.end(); itEnd++) {
			auto end = (*itEnd);

			Glue *glue;
			if ((glue = dynamic_cast<Glue *>(end.get()))) {
				glueSize += glue->getSize();
				minGlueSize += glue->getMinSize();
				maxGlueSize += glue->getMaxSize();
			}
			else {
				sizeOfBoxes += getBoxSize(end);
			}

			/*
			 * list size may never exceed maximum size
			 */
			if (sizeOfBoxes + minGlueSize > maxSize)
				break;

			if (!glue)
				continue;

			actualGlueSize = maxSize - sizeOfBoxes;
			naturalSize = sizeOfBoxes + glueSize;

			float ratio = 0;
			if (naturalSize == maxSize)
				ratio = 0;
			else if (naturalSize < maxSize)
				ratio = (float)actualGlueSize / maxGlueSize;
			else if (minGlueSize > actualGlueSize)
				ratio = (float)minGlueSize / actualGlueSize;

			listBadness = min(100 * pow(ratio, 3), 1e4);

			/*
			 * relax current (end) vertice if possible
			 */
			newBadness = begin->getBadness() + listBadness;
			if (newBadness < end->getBadness()) {
				end->setBadness(newBadness);
				end->setPrev(begin);
			}
		}
	}

	/*
	 * least-cost (minimum total badness) path (division) reconstruction
	 * using a doubly-linked list for convenience
	 *
	 * to start with, glueE (*inner.back()) is used as it is present in every
	 * division, and so in every minimum division
	 */
	list<shared_ptr<Box>> divPoints;
	auto divPoint = inner.back();
	while (divPoint.get()) {
		divPoints.emplace_front(divPoint);
		divPoint = divPoint->getPrev();
	}

	divPoints.pop_front();		/* glue0 always present, remove it */

	inner.erase(inner.begin());	/* remove glue0 so it won't render */

	shared_ptr<List> lastList;
	auto beginIt = inner.begin(), endIt = beginIt;

	while (!divPoints.empty()) {
		divPoint = divPoints.front();

		if (divPoint.get() == glue0)
			continue;

		/*
		 * search for current divPoint (guaranteed to be found)
		 */
		while (*endIt != divPoint)
			endIt++;

		if (beginIt == endIt)
			break;

		auto newList = createNewList(beginIt, endIt);
		boxes.push_back(newList);
		boxes.push_back(createNewInterlineGlue());

		beginIt = endIt + 1;	/* step over the glue */
		endIt = beginIt;

		lastList = newList;
		divPoints.pop_front();
	}

	/*
	 * append an infinitely-stretchable glue to the end of last list
	 */
	if (lastList)
		lastList->addChild(createNewInfGlue());
}
