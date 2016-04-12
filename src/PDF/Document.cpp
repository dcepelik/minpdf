#include <iomanip>

#include "Document.hpp"

using namespace PDF::Objects;
using namespace PDF;


Document::Document()
{
}


void
Document::preparePDFObjects()
{	
}


void
Document::addPage(shared_ptr<Page> page)
{
	docPages.push_back(page);
}


void
Document::writePDFOutput(Writer &writer)
{
	writer.writePDFHeader();

	IndirectObject<Dictionary> catalog;
	IndirectObject<Dictionary> pages;
	Array kids;
	Dictionary trailer;
	Dictionary fonts;
	IndirectObject<Dictionary> defaultFont;

	catalog.getInner().addItem("Type", new Name("Catalog"));
	catalog.getInner().addItem("Pages", pages.getReference().get());

	pages.getInner().addItem("Type", new Name("Pages"));
	pages.getInner().addItem("Kids", &kids);
	pages.getInner().addItem("Count", new Number(docPages.size()));

	trailer.addItem("Root", catalog.getReference().get());
	trailer.addItem("Size", new Number(5)); // TODO

	defaultFont.getInner().addItem("Type", new Name("Font"));
	defaultFont.getInner().addItem("Subtype", new Name("Type1"));
	defaultFont.getInner().addItem("Name", new Name("F1"));
	defaultFont.getInner().addItem("BaseFont", new Name("Courier"));
	defaultFont.getInner().addItem("Encoding", new Name("MacRomanEncoding"));

	fonts.addItem("F1", defaultFont.getReference().get());

	vector<unique_ptr<Reference>> pageRefs;

	for (auto docPage: docPages) {
		Dictionary resources;
		resources.addItem("Font", &fonts);

		/* page content stream */
		IndirectObject<Stream> stream(Stream(docPage->contents()));
		stream.writePDFOutput(writer);

		/* page definition dictionary */
		IndirectObject<Dictionary> pageDef;
		pageDef.getInner().addItem("Type", new Name("Page"));
		pageDef.getInner().addItem("Parent", pages.getReference().get());

		pageDef.getInner().addItem("MediaBox", new Literal("[0 0 612 792]"));
		writer.writeEOL();

		pageDef.getInner().addItem("Contents", stream.getReference().get());
		pageDef.getInner().addItem("Resources", &resources);

		/* PDF::Objects::Reference needs to survive this block */
		pageRefs.push_back(move(pageDef.getReference()));
	}

	for (auto &pageRef: pageRefs) {
		kids.addChild(pageRef.get());
	}

	catalog.writePDFOutput(writer);
	pages.writePDFOutput(writer);
	defaultFont.writePDFOutput(writer);

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
