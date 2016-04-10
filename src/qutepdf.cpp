#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

#include "Parser.hpp"
#include "PDF/Document.hpp"
#include "PDF/Objects/Dictionary.hpp"
#include "PDF/Objects/Array.hpp"
#include "PDF/Objects/Object.hpp"

using namespace std;
using namespace PDF;
using namespace PDF::Objects;


void
usage(string argv0) {
	cerr << argv0 << ": usage: " << argv0 << " <input_file> <output_file>"
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

	istream stream(&buf);
	Parser p(stream);
	shared_ptr<Element> doc = p.parseDocument();

	vector<shared_ptr<Box>> boxes;
	doc->expand(boxes);

	/* -b switch
	for (auto it = boxes.begin(); it != boxes.end(); it++) {
		(*it)->dump();
	}
	cout << endl;
	*/

	buf.close();

	PDF::Document *pdfDoc = new PDF::Document();
	Page *page = new Page("BT\r\n/F1 24 Tf\r\n100 100 Td\r\n\r\n( Hello World ) Tj");

	pdfDoc->addPage(shared_ptr<Page>(page));

	pdfDoc->print(ofs);

	return EXIT_SUCCESS;
}
