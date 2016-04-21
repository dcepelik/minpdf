#include "List.hpp"

using namespace BoxModel;


List::List() : Container() {}


void
List::writePSOutput(ostream &out)
{
	int maxWidth = 612;

	int width = 0;
	int height = 0;
	int glueCount = 0;
	for (auto item: items) {
		if (item->getType() == HorizontalGlueBox) {
			glueCount++;
		}
		else {
			width += item->getWidth();
			height = max(height, item->getHeight());
		}
	}

	int avgWidthOfGlue = 0;
	if (glueCount > 0)
		avgWidthOfGlue = (maxWidth - width) / glueCount;

	int realWidth = 0;
	for (auto item: items) {
		if (item->getType() == HorizontalGlueBox)
			item->setWidth(avgWidthOfGlue);

		item->writePSOutput(out);
		realWidth += item->getWidth();
	}

	out << -realWidth << " " << -height << " Td ";
}
