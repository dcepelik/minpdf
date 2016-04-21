#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

#include "BoxModel/Box.hpp"
#include "Input/Parser.hpp"
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
	buf.close();

	//doc->dump();

	shared_ptr<Style> defaultStyle(new Style());
	defaultStyle->fontFamily = "/F1";
	defaultStyle->fontSize = 11;

	shared_ptr<StyleTable> table(new StyleTable());
	table->addStyle("p", defaultStyle);

	doc->setStyleTable(table);

	doc->renderPDFOutput(ofs);

	cout << endl << "Done." << endl;

	return EXIT_SUCCESS;
}
