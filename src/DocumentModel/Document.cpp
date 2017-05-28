#include <sstream>

#include "BoxModel/HList.hpp"
#include "BoxModel/InlinePostscript.hpp"
#include "BoxModel/Line.hpp"
#include "BoxModel/VList.hpp"
#include "Document.hpp"
#include "Elements/Paragraph.hpp"
#include "Elements/StaticContainer.hpp"
#include "Elements/TextNode.hpp"
#include "PDF/Document.hpp"
#include "PDF/Writer.hpp"
#include "PS/Writer.hpp"

namespace DM = DocumentModel;


void DM::Document::prerender(vector<shared_ptr<Box>> &boxes)
{
	/* get "flat" representation of the document */
	vector<shared_ptr<Element>> children;
	getChildrenRecursive(children);

	for (auto child: children) {
		//cerr << child->name << endl;
		if (child->name != "1" && child->name != "2" && child->name != "3")
			continue;

		int level = stoi(child->name);

		Paragraph *pageNoPar = new Paragraph(shared_ptr<Element>(this), contentWidth);

		HGlue *indent = new HGlue(0, 20 * (level - 1), 0, 0);
		StaticContainer *indentContainer = new StaticContainer(shared_ptr<Element>(pageNoPar));
		indentContainer->addBox(shared_ptr<Box>(indent));

		TextNode *tn = new TextNode(shared_ptr<Element>(pageNoPar), child->getTextualContent());
		pageNoPar->addChild(shared_ptr<Element>(indentContainer));
		pageNoPar->addChild(shared_ptr<Element>(tn));

		pageNoPar->render(boxes);
	}
}


void
DM::Document::renderPDFOutput(ostream &out)
{
	int pageNo = 1;

	Writer writer(out);
	shared_ptr<PDF::Document> doc(new PDF::Document);

	vector<shared_ptr<Box>> boxes;
	this->render(boxes);

	/* now we should have one VList per output page */

	for (auto box: boxes) {
		if (!dynamic_cast<VList *>(box.get()))
			continue;

		Paragraph *pageNoPar = new Paragraph(shared_ptr<Element>(this), 200);
		TextNode *tn = new TextNode(shared_ptr<Element>(pageNoPar), "Page " + to_string(pageNo));
		pageNoPar->addChild(shared_ptr<Element>(tn));

		Line *line = new Line(getContentWidth(), 0, 0, true);

		vector<shared_ptr<Box>> tmp;
		tmp.push_back(shared_ptr<Box>(line));
		pageNoPar->render(tmp);

		VList *vMargins = new VList(pageHeight);
		vMargins->addChild(shared_ptr<Box>(new VGlue(0, 100, 0, 0)));
		vMargins->addChild(box);
		vMargins->addChild(shared_ptr<Box>(new VGlue(1, 0, 0, 0)));
		for (auto box: tmp)
			vMargins->addChild(box);
		vMargins->addChild(shared_ptr<Box>(new VGlue(1, 0, 0, 0)));

		HList hMargins(pageWidth);
		hMargins.addChild(shared_ptr<Box>(new HGlue(1, 0, 200, 0)));
		hMargins.addChild(shared_ptr<Box>(vMargins));
		hMargins.addChild(shared_ptr<Box>(new HGlue(1, 0, 200, 0)));

		stringstream ps;
		PS::Writer psWriter(ps);

		psWriter.writeTd(0, 842.25); /* TODO */
		hMargins.writePSOutput(psWriter);

		shared_ptr<PDF::Page> page(new PDF::Page(ps.str()));
		doc->addPage(page);

		pageNo++;
	}

	doc->writePDFOutput(writer);
}
