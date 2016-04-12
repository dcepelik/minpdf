#include <iomanip>

#include "Document.hpp"

using namespace PDF::Objects;
using namespace PDF;


Document::Document()
{
	pageRefs = shared_ptr<Array>(new Array());
	fonts = shared_ptr<Dictionary>(new Dictionary());
}


void
Document::preparePDFObjects()
{	
	catalog.wrapped()->addItem("Type", new Name("Catalog"));
	catalog.wrapped()->addItem("Pages", pageCatalog.getRef());

	pageCatalog.wrapped()->addItem("Type", new Name("Pages"));
	pageCatalog.wrapped()->addItem("Kids", pageRefs);
	pageCatalog.wrapped()->addItem("Count", new Number(pages.size()));

	trailer.addItem("Root", catalog.getRef());
	trailer.addItem("Size", new Number(Object::objectCount() + 1));

	fonts->addItem("F1", helveticaFont.getRef());

	helveticaFont.wrapped()->addItem("Type", new Name("Font"));
	helveticaFont.wrapped()->addItem("Subtype", new Name("Type1"));
	helveticaFont.wrapped()->addItem("Name", new Name("F1"));
	helveticaFont.wrapped()->addItem("BaseFont", new Name("Courier"));
	helveticaFont.wrapped()->addItem("Encoding", new Name("MacRomanEncoding"));
}


void
Document::addPage(shared_ptr<Page> page)
{
	pages.push_back(page);

	Dictionary *pageResources = new Dictionary();
	pageResources->addItem("Font", fonts);

	/* page content-stream */
	auto pageStream = new IndirectObject<Stream>(
		shared_ptr<Stream>(new Stream(page->contents()))
	);
	pageStreams.push_back(shared_ptr<IndirectObject<Stream>>(pageStream));

	/* page definition dictionary */
	auto pageDef = new IndirectObject<Dictionary>();
	pageDef->wrapped()->addItem("Type", new Name("Page"));
	pageDef->wrapped()->addItem("Parent", pageCatalog.getRef());
	pageDef->wrapped()->addItem("MediaBox", new Literal("[0 0 612 792]\r\n"));
	pageDef->wrapped()->addItem("Contents", pageStream->getRef());
	pageDef->wrapped()->addItem("Resources", shared_ptr<Object>(pageResources));

	pageDefs.push_back(shared_ptr<IndirectObject<Dictionary>>(pageDef));


	pageRefs->addChild(pageDef->getRef());
}


void
Document::writePDFOutput(Writer &writer)
{
	preparePDFObjects();

	vector<int> xref;

	writer.writePDFHeader();

	catalog.writePDFOutput(writer);
	pageCatalog.writePDFOutput(writer);
	helveticaFont.writePDFOutput(writer);

	for (auto pageStream: pageStreams) {
		pageStream->writePDFOutput(writer);
	}

	for (auto pageDef: pageDefs) {
		pageDef->writePDFOutput(writer);
	}

	writer.writeLine("trailer");
	trailer.writePDFOutput(writer);

	writer.writeXrefTable();
	writer.writeEOF();
}
