#include <iostream>
#include <stdexcept>
#include <string>

#include "DocumentModel/Document.hpp"
#include "Element.hpp"

using namespace DocumentModel::Elements;
using namespace DocumentModel;
using namespace std;


Document *
Element::getDocument()
{
	shared_ptr<Element> p = parent;
	while (p.get() != NULL) {
		Document *doc;
		if ((doc = dynamic_cast<Document *>(p.get()))) {
			return doc;
		}

		p = p->getParent();
	}

	return NULL;
}

