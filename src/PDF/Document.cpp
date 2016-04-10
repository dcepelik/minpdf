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
	pageCatalog.wrapped()->addItem("Children", &pageRefs);

	trailer.addItem("Root", catalog.getRef());
	trailer.addItem("Size", new Number(Object::objectCount()));
}


void
Document::addPage(shared_ptr<Page> page)
{
	preparePDFObjects();

	pages.push_back(page);

	/* page content-stream */
	auto pageStream = new IndirectObject<Stream>(
		shared_ptr<Stream>(new Stream(page->contents()))
	);
	pageStreams.push_back(shared_ptr<IndirectObject<Stream>>(pageStream));

	/* page definition dictionary */
	auto pageDef = new IndirectObject<Dictionary>();
	pageDef->wrapped()->addItem("Type", new Name("Page"));
	pageDef->wrapped()->addItem("Parent", pageCatalog.getRef());
	pageDef->wrapped()->addItem("Contents", pageStream->getRef());
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
	vector<int> xref;

	out << "%PDF-1.4" << endl;

	printObjAndPushXref(out, catalog, xref);
	printObjAndPushXref(out, pageCatalog, xref);

	for (auto pageDef: pageDefs) {
		printObjAndPushXref(out, *pageDef, xref);
	}

	for (auto pageStream: pageStreams) {
		printObjAndPushXref(out, *pageStream, xref);
	}

	out << "xref 0 " << (xref.size() + 1) << endl;
	out << "0000000000 65535 f" << endl;

	for (auto offset: xref) {
		out << setfill('0') << setw(10) << offset << " 00000 n" << endl;
	}

	out << "trailer " << trailer;
	out << "startxref" << endl;
	out << out.tellp() << endl;
	out << "%%EOF" << endl;
}
