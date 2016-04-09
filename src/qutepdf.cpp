#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

#include "Parser.hpp"

using namespace std;


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
	p.parseDocument();

	buf.close();

	return EXIT_SUCCESS;
}
