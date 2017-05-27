#include <iostream>
#include <stdexcept>
#include <string>
#include <cassert>

#include "DocumentModel/Document.hpp"
#include "Element.hpp"

using namespace DocumentModel::Elements;
using namespace DocumentModel;
using namespace std;


Document *Element::getDocument()
{
	Element *p = this;

	while (p != NULL) {
		Document *doc;
		if ((doc = dynamic_cast<Document *>(p))) {
			return doc;
		}

		p = p->getParent();
	}

	return NULL;
}


unique_ptr<Style> Element::getStyle()
{
	unique_ptr<Style> s;
	Style *elStyle;

	assert(parent.get() != this);

	if (!parent) {
		s = unique_ptr<Style>(new Style());
		s->fontFamily = "/F1";
		s->fontSize = 11;
	}
	else {
		s = parent->getStyle();
	}

	assert(parent != NULL || getDocument() == this);

	elStyle = getDocument()->getStyleTable()->getStyle(name);
	if (elStyle)
		s->patch(elStyle);

	return s;
}

