#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

#include "BoxModel/Box.hpp"
#include "Input/Parser.hpp"
#include "PDF/Writer.hpp"
#include "PDF/Document.hpp"
#include "PS/Writer.hpp"
#include "PDF/Objects/Object.hpp"
#include "DocumentModel/Elements/Paragraph.hpp"

using namespace BoxModel;
using namespace Input;
using namespace std;


void
usage(string argv0) {
	cout << argv0 << ": usage: " << argv0 << " <input_file> <output_file>"
		<< endl;
}


int
main(int argc, char *argv[]) {
	if (argc != 3) {
		usage(argv[0]);
		return EXIT_FAILURE;
	}

	string input_fn = argv[1];
	string output_fn = argv[2];

	filebuf buf;
	if (!buf.open(input_fn, ios::in)) {
		cerr << "Cannot open file '" << input_fn << "' for reading"
			<< endl;
		return EXIT_FAILURE;
	}

	ofstream ofs;
	ofs.open(output_fn, ofstream::out);

	/* @todo ofs? */

	istream stream(&buf);
	Parser p(stream);
	shared_ptr<DocumentModel::Document> doc = p.parseDocument();

	shared_ptr<Style> defaultStyle(new Style());
	defaultStyle->fontFamily = "/F1";
	defaultStyle->fontSize = 13;

	shared_ptr<StyleTable> table(new StyleTable());
	table->addStyle("p", defaultStyle);

	doc->setStyleTable(table);

	buf.close();

	vector<shared_ptr<Box>> boxes;
	doc->render(boxes);

	doc->dump();

	stringstream psStream;
	psStream << "0 752 Td\r\n";

	PS::Writer psWriter(psStream);
	for (auto box: boxes) {
		box->dump(cerr);
		box->writePSOutput(psWriter);
	}
	cout << endl;

	shared_ptr<PDF::Document> pdfDoc(new PDF::Document);
	shared_ptr<PDF::Page> pdfPage(new PDF::Page(psStream.str()));
	pdfDoc->addPage(pdfPage);

	Writer writer(ofs);
	pdfDoc->writePDFOutput(writer);

	cout << "Done." << endl;

	return EXIT_SUCCESS;
}
