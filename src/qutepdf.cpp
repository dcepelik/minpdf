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

	string infile = argv[1];
	string outfile = argv[2];

	filebuf buf;
	if (!buf.open(infile, ios::in)) {
		cerr << "Cannot open file '" << infile << "' for reading"
			<< endl;
		return EXIT_FAILURE;
	}

	istream stream(&buf);
	Parser p(stream);
	shared_ptr<Element> doc = p.parseDocument();

	vector<shared_ptr<Box>> boxes;
	doc->expand(boxes);

	for (auto it = boxes.begin(); it != boxes.end(); it++) {
		//(*it)->dump();
	}
	cout << endl;

	buf.close();

	auto arr = new Dictionary();
	arr->addItem("Srot", shared_ptr<Object>(new Array()));
	cout << (*arr);

	return EXIT_SUCCESS;
}
