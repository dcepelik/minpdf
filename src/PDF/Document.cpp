#include <iomanip>

#include "Document.hpp"

using namespace PDF::Objects;
using namespace PDF;


Document::Document()
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

	auto pagesRef = pages.getReference();
	catalog.getInner().addItem("Pages", pagesRef.get());

	pages.getInner().addItem("Type", new Name("Pages"));
	pages.getInner().addItem("Kids", &kids);
	pages.getInner().addItem("Count", new Number(docPages.size()));

	auto catalogRef = catalog.getReference();
	trailer.addItem("Root", catalogRef.get());
	trailer.addItem("Size", new Number(6)); // TODO

	defaultFont.getInner().addItem("Type", new Name("Font"));
	defaultFont.getInner().addItem("Subtype", new Name("Type1"));
	defaultFont.getInner().addItem("Name", new Name("F1"));
	defaultFont.getInner().addItem("BaseFont", new Name("Courier"));
	defaultFont.getInner().addItem("Encoding", new Name("MacRomanEncoding"));

	auto defaultFontRef = defaultFont.getReference();
	fonts.addItem("F1", defaultFontRef.get());

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

		auto pagesRef = pages.getReference();
		pageDef.getInner().addItem("Parent", pagesRef.get());

		pageDef.getInner().addItem("MediaBox", new Literal("[0 0 612 792]\r\n"));

		auto streamRef = stream.getReference();
		pageDef.getInner().addItem("Contents", streamRef.get());
		pageDef.getInner().addItem("Resources", &resources);

		pageDef.writePDFOutput(writer);

		/* PDF::Objects::Reference needs to survive this block */
		pageRefs.push_back(move(pageDef.getReference()));
	}

	for (auto &pageRef: pageRefs) {
		kids.addChild(pageRef.get());
	}

	catalog.writePDFOutput(writer);
	pages.writePDFOutput(writer);
	defaultFont.writePDFOutput(writer);

	writer.writeLine("trailer");
	trailer.writePDFOutput(writer);

	writer.writeXrefTable();
	writer.writeStartXref();
	writer.writeEOF();
}
