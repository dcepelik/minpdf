#include <sstream>

#include "Document.hpp"
#include "PDF/Document.hpp"
#include "PDF/Writer.hpp"
#include "PS/Writer.hpp"
#include "BoxModel/VList.hpp"

namespace DM = DocumentModel;


DM::Document::Document() : VWrappingContainer(shared_ptr<Element>(this), "document", 762)
{
}


void
DM::Document::setStyleTable(shared_ptr<StyleTable> styleTable)
{
	this->styleTable = styleTable;
}


shared_ptr<StyleTable>
DM::Document::getStyleTable()
{
	return styleTable;
}


void
DM::Document::renderPDFOutput(ostream &out)
{
	shared_ptr<PDF::Document> doc(new PDF::Document);

	vector<shared_ptr<Box>> boxes;
	this->render(boxes);

	for (auto box: boxes) {
		if (!dynamic_cast<VList *>(box.get()))
			continue;

		stringstream ps;
		PS::Writer psWriter(ps);

		ps << "0 752 Td\r\n";	/* TODO */
		box->writePSOutput(psWriter);

		shared_ptr<PDF::Page> page(new PDF::Page(ps.str()));
		doc->addPage(page);
	}

	Writer writer(out);
	doc->writePDFOutput(writer);
}
