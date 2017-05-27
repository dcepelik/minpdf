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
	IndirectObject<Dictionary> timesRomanFont;
	IndirectObject<Dictionary> timesBoldFont;
	IndirectObject<Dictionary> timesItalicFont;
	IndirectObject<Dictionary> courierFont;

	catalog.getInner().addItem("Type", new Name("Catalog"));

	auto pagesRef = pages.getReference();
	catalog.getInner().addItem("Pages", pagesRef.get());

	pages.getInner().addItem("Type", new Name("Pages"));
	pages.getInner().addItem("Kids", &kids);
	pages.getInner().addItem("Count", new Number(docPages.size()));

	auto catalogRef = catalog.getReference();
	trailer.addItem("Root", catalogRef.get());
	trailer.addItem("Size", new Number(6)); // TODO

	timesRomanFont.getInner().addItem("Type", new Name("Font"));
	timesRomanFont.getInner().addItem("Subtype", new Name("Type1"));
	timesRomanFont.getInner().addItem("Name", new Name("F1"));
	timesRomanFont.getInner().addItem("BaseFont", new Name("Times-Roman"));
	timesRomanFont.getInner().addItem("Encoding", new Name("MacRomanEncoding"));

	timesBoldFont.getInner().addItem("Type", new Name("Font"));
	timesBoldFont.getInner().addItem("Subtype", new Name("Type1"));
	timesBoldFont.getInner().addItem("Name", new Name("F3"));
	timesBoldFont.getInner().addItem("BaseFont", new Name("Times-Bold"));
	timesBoldFont.getInner().addItem("Encoding", new Name("MacRomanEncoding"));

	timesItalicFont.getInner().addItem("Type", new Name("Font"));
	timesItalicFont.getInner().addItem("Subtype", new Name("Type1"));
	timesItalicFont.getInner().addItem("Name", new Name("F4"));
	timesItalicFont.getInner().addItem("BaseFont", new Name("Times-Italic"));
	timesItalicFont.getInner().addItem("Encoding", new Name("MacRomanEncoding"));

	courierFont.getInner().addItem("Type", new Name("Font"));
	courierFont.getInner().addItem("Subtype", new Name("Type1"));
	courierFont.getInner().addItem("Name", new Name("F2"));
	courierFont.getInner().addItem("BaseFont", new Name("Courier"));
	courierFont.getInner().addItem("Encoding", new Name("MacRomanEncoding"));

	auto timesRomanFontRef = timesRomanFont.getReference();
	fonts.addItem("F1", timesRomanFontRef.get());

	auto timesBoldFontRef = timesBoldFont.getReference();
	fonts.addItem("F3", timesBoldFontRef.get());

	auto timesItalicFontRef = timesItalicFont.getReference();
	fonts.addItem("F4", timesItalicFontRef.get());

	auto courierFontRef = courierFont.getReference();
	fonts.addItem("F2", courierFontRef.get());

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

		/*
		 * A4 MediaBox size taken from
		 * http://www.telerik.com/forums/export-to-pdf-what-is-the-correct-mediabox-size-for-a4
		 */
		pageDef.getInner().addItem("MediaBox", new Literal("[0 0 594.75 842.25]\r\n"));

		auto streamRef = stream.getReference();
		pageDef.getInner().addItem("Contents", streamRef.get());
		pageDef.getInner().addItem("Resources", &resources);

		pageDef.writePDFOutput(writer);

		/* PDF::Objects::Reference needs to survive this block */
		pageRefs.push_back(pageDef.getReference());
	}

	for (auto &pageRef: pageRefs) {
		kids.addChild(pageRef.get());
	}

	catalog.writePDFOutput(writer);
	pages.writePDFOutput(writer);
	timesRomanFont.writePDFOutput(writer);
	timesBoldFont.writePDFOutput(writer);
	timesItalicFont.writePDFOutput(writer);
	courierFont.writePDFOutput(writer);

	writer.writeLine("trailer");
	trailer.writePDFOutput(writer);

	writer.writeXrefTable();
	writer.writeStartXref();
	writer.writeEOF();
}
