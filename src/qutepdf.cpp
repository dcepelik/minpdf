#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

#include "PDF/Writer.hpp"
#include "PDF/Objects/Object.hpp"
#include "Input/Parser.hpp"
#include "Renderer.hpp"

using namespace std;
using namespace Input;


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

	/* @todo ofs? */

	istream stream(&buf);
	Parser p(stream);
	shared_ptr<Element> doc = p.parseDocument();

	buf.close();

	Renderer *renderer = new Renderer();
	
	vector<shared_ptr<Box>> boxes;
	doc->expand(boxes);

	renderer->render(boxes);

	stringstream ps;
	ps << "0 752 Td\r\n";
	for (auto box: boxes) {
		box->dump();
		box->writePSOutput(ps);
	}
	cout << endl;

	shared_ptr<PDF::Document> pdfDoc(new PDF::Document);
	shared_ptr<PDF::Page> pdfPage(new PDF::Page(ps.str()));
	pdfDoc->addPage(pdfPage);

	Writer writer(ofs);
	pdfDoc->writePDFOutput(writer);


	cout << "Done." << endl;

	return EXIT_SUCCESS;
}
