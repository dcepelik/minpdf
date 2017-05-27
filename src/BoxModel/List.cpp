#include <climits>
#include <cmath>

#include "Glue.hpp"
#include "List.hpp"

using namespace BoxModel;


void
List::divideSpaces()
{
	double size = 0;
	int maxCardinality = INT_MIN;	/* maximum cardinality among the glues */

	for (auto child: children) {
		if (Glue *glue = dynamic_cast<Glue *>(child.get())) {
			maxCardinality =
				max(maxCardinality, glue->getCardinality());

			size += glue->getMinSize();
			glue->setActualSize(glue->getMinSize()); /* TODO */
		}
		else {
			size += getBoxSize(child);
		}
	}

	vector<Glue *> glues;
	for (auto child: children) {
		if (Glue *glue = dynamic_cast<Glue *>(child.get())) {
			if (glue->getCardinality() == maxCardinality)
				glues.push_back(glue);
		}
	}

	double toStretch = maxSize - size;

	vector<Glue *>::size_type numFailed = 0;
	bool overstretch = false;

	for (auto glue: glues) {
		glue->setActualSize(glue->getActualSize() + toStretch / glues.size());
		if (glue->getActualSize() > glue->getMaxSize()) {
			numFailed++;
			overstretch = true;
		}
	}

	if (overstretch) {
		/* TODO exception */
		cerr << "List::divideSpaces(): Some glues were overstretched"
			<< endl;
	}
}
