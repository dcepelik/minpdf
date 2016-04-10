#include <iomanip>

#include "Document.hpp"

using namespace PDF;
using namespace PDF::Objects;


Document::Document()
{
}


void
Document::preparePDFObjects()
{	
	catalog.wrapped()->addItem("Type", new Name("Catalog"));
	catalog.wrapped()->addItem("Pages", pageCatalog.getRef());

	pageCatalog.wrapped()->addItem("Type", new Name("Pages"));
	pageCatalog.wrapped()->addItem("Kids", &pageRefs);
	pageCatalog.wrapped()->addItem("Count", new Number(pages.size()));

	trailer.addItem("Root", catalog.getRef());
	trailer.addItem("Size", new Number(Object::objectCount() + 1));

	fonts.addItem("F1", helveticaFont.getRef());

	helveticaFont.wrapped()->addItem("Type", new Name("Font"));
	helveticaFont.wrapped()->addItem("Subtype", new Name("Type1"));
	helveticaFont.wrapped()->addItem("Name", new Name("F1"));
	helveticaFont.wrapped()->addItem("BaseFont", new Name("Helvetica"));
	helveticaFont.wrapped()->addItem("Encoding", new Name("MacRomanEncoding"));
}


void
Document::addPage(shared_ptr<Page> page)
{
	pages.push_back(page);

	Dictionary *pageResources = new Dictionary();
	pageResources->addItem("Font", shared_ptr<Object>(&fonts));

	/* page content-stream */
	auto pageStream = new IndirectObject<Stream>(
		shared_ptr<Stream>(new Stream(page->contents()))
	);
	pageStreams.push_back(shared_ptr<IndirectObject<Stream>>(pageStream));

	/* page definition dictionary */
	auto pageDef = new IndirectObject<Dictionary>();
	pageDef->wrapped()->addItem("Type", new Name("Page"));
	pageDef->wrapped()->addItem("Parent", pageCatalog.getRef());
	pageDef->wrapped()->addItem("MediaBox", new Literal("[0 0 612 792]"));
	pageDef->wrapped()->addItem("Contents", pageStream->getRef());
	pageDef->wrapped()->addItem("Resources",
		shared_ptr<Object>(pageResources));
	pageDefs.push_back(shared_ptr<IndirectObject<Dictionary>>(pageDef));


	pageRefs.addChild(pageDef->getRef());
}


void
Document::printObjAndPushXref(ostream &out, Object &obj, vector<int> &xref)
{
	xref.push_back(out.tellp()); /* tellp(): won't work for cout */
	out << obj;
}


void
Document::print(ostream &out)
{
	preparePDFObjects();

	vector<int> xref;

	/* http://stackoverflow.com/questions/23433650 */
	string comment8bit = "\r%\xE2\xE3\xCF\xD3";
	out << "%PDF-1.4" << comment8bit << "\r\n";

	printObjAndPushXref(out, catalog, xref);
	printObjAndPushXref(out, pageCatalog, xref);
	printObjAndPushXref(out, helveticaFont, xref);

	for (auto pageStream: pageStreams) {
		printObjAndPushXref(out, *pageStream, xref);
	}

	for (auto pageDef: pageDefs) {
		printObjAndPushXref(out, *pageDef, xref);
	}

	int xrefOffset = out.tellp();
	out << "xref" << "\r\n";

	out << "0 " << (xref.size() + 1) << "\r\n";
	out << "0000000000 65535 f" << "\r\n";

	for (auto offset: xref) {
		out << setfill('0') << setw(10) << offset << " 00000 n" << "\r\n";
	}

	out << "trailer " << trailer;
	out << "startxref" << "\r\n";
	out << xrefOffset << "\r\n";
	out << "%%EOF" << "\r\n";
}
