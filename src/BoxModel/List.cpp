#include <climits>
#include <cmath>

#include "Glue.hpp"
#include "List.hpp"

using namespace BoxModel;


void
List::divideSpaces()
{
	int size = 0;
	int maxCardinality = INT_MIN;

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

	int totalGlueSize = maxSize - size;

	vector<Glue *>::size_type numFailed = 0;
	bool overstretch = false;

	/* TODO: take care of cycles */
	for (int i = 0; glues.size() > 0 && totalGlueSize > 0; i = (i + 1) % glues.size()) {
		int size = glues[i]->getActualSize();

		if (overstretch || size < glues[i]->getMaxSize()) {
			glues[i]->setActualSize(size + 1);
			totalGlueSize--;

			numFailed = 0;
		}
		else {
			numFailed++;
		}

		overstretch = overstretch || numFailed == glues.size();
	}

	if (overstretch) {
		/* TODO exception */
		cerr << "List::divideSpaces(): Some glues were overstretched"
			<< endl;
	}
}
