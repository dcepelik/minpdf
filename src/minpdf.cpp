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
	Parser p(stream, input_fn);
	shared_ptr<DocumentModel::Document> doc = p.parseDocument();
	buf.close();

	doc->dump(0);

	shared_ptr<StyleTable> table(new StyleTable());

	unique_ptr<Style> pStyle(new Style());
	pStyle->setFontFamily("/F1");
	pStyle->setFontSize(12);
	table->addStyle("p", move(pStyle));

	unique_ptr<Style> titleStyle(new Style());
	titleStyle->setFontSize(28);
	titleStyle->setFontFamily("/F3");
	table->addStyle("title", move(titleStyle));

	for (int i = 1; i <= 3; i++) {
		unique_ptr<Style> headlineStyle(new Style());
		headlineStyle->setFontSize(20 - 5 * (i - 1));
		if (i >= 3)
			headlineStyle->setFontFamily("/F3");
		table->addStyle(to_string(i), move(headlineStyle));
	}

	unique_ptr<Style> ttStyle(new Style());
	ttStyle->setFontFamily("/F2");
	table->addStyle("tt", move(ttStyle));

	unique_ptr<Style> bfStyle(new Style());
	bfStyle->setFontFamily("/F3");
	table->addStyle("bf", move(bfStyle));

	unique_ptr<Style> itStyle(new Style());
	itStyle->setFontFamily("/F4");
	table->addStyle("it", move(itStyle));

	doc->setStyleTable(table);
	doc->renderPDFOutput(ofs);

	cout << endl << "Done." << endl;

	return EXIT_SUCCESS;
}
