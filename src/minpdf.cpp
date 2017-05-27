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

	shared_ptr<StyleTable> table(new StyleTable());

	unique_ptr<Style> pStyle(new Style());
	pStyle->fontFamily = "/F1";
	pStyle->fontSize = 12;
	table->addStyle("p", move(pStyle));

	unique_ptr<Style> titleStyle(new Style());
	titleStyle->fontFamily = "/F1";
	titleStyle->fontSize = 28;
	table->addStyle("title", move(titleStyle));

	for (int i = 1; i <= 3; i++) {
		unique_ptr<Style> headlineStyle(new Style());
		headlineStyle->fontFamily = "/F1";
		headlineStyle->fontSize = 20 - 3 * (i - 1);

		table->addStyle(to_string(i), move(headlineStyle));
	}

	doc->setStyleTable(table);
	doc->renderPDFOutput(ofs);

	cout << endl << "Done." << endl;

	return EXIT_SUCCESS;
}
