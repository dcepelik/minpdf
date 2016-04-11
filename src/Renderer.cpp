#include <sstream>

#include "Renderer.hpp"
#include "BoxModel/Char.hpp"

using namespace std;
using namespace BoxModel;


Renderer::Renderer()
{
}


void
Renderer::formatLine(vector<shared_ptr<Box>>::iterator start,
	vector<shared_ptr<Box>>::iterator end, int y)
{
	int numStretchable = 0;
	int lineWidth = 0;
	int lineHeight = 25;

	for (auto it = start; it != end; it++) {
		lineWidth += (*it)->getWidth();

		if ((*it)->getStretchability() > 0)
			numStretchable++;
	}

	int avgStretch = (612 - lineWidth) / numStretchable;

	int x = 0;
	for (auto it = start; it != end; it++) {
		if ((*it)->getStretchability() > 0) {
			(*it)->setWidth(avgStretch);
		}

		(*it)->setOrigin(x, y);
		x += (*it)->getWidth();
	}
}


void
Renderer::typesetBoxes()
{
	int margin = 30;

	int maxLineWidth = 612;

	int lineWidth = 0;
	int y = 600;

	auto start = boxes.begin(), end = start;
	for (auto it = boxes.begin(); it != boxes.end(); it++) {
		if ((*it)->getStretchability() > 0) {
			end = it;
		}
		else {
			if (2 * margin + lineWidth + (*it)->getWidth() > maxLineWidth) {
				formatLine(start, end, y);
				start = end;
				y -= 25;
				lineWidth = 0;
				it = end;
			}
			else {
				lineWidth += (*it)->getWidth();
			}
		}
	}

	if (end != boxes.end())
		formatLine(end, boxes.end(), y);
}


shared_ptr<PDF::Document>
Renderer::render(shared_ptr<Element> doc)
{
	doc->expand(boxes);

	typesetBoxes();

	stringstream postscript;
	for (auto box: boxes) {
		box->print(postscript);
	}

	PDF::Document *pdfDoc = new PDF::Document();
	Page *page = new Page(postscript.str());

	pdfDoc->addPage(shared_ptr<Page>(page));

	return shared_ptr<PDF::Document>(pdfDoc);
}
