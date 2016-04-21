#include "Document.hpp"

using namespace DocumentModel;


Document::Document() : Container(shared_ptr<Element>(this), "document")
{
}


void
Document::setStyleTable(shared_ptr<StyleTable> styleTable)
{
	this->styleTable = styleTable;
}


shared_ptr<StyleTable>
Document::getStyleTable()
{
	return styleTable;
}
