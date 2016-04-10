#include "Stream.hpp"
#include "Dictionary.hpp"
#include "Number.hpp"

using namespace PDF::Objects;
using namespace std;


Stream::Stream()
{
}


Stream::Stream(string content)
{
	this->content = content;
}


void
Stream::printInternal(ostream &out) const
{
	Dictionary dict;
	int size = content.size();
	dict.addItem("Length", new Number(size));

	dict.print(out);
	out << "stream" << "\r\n";
	out << content;
	out << "\r\n" << "endstream" << "\r\n"; /* "\r\n" prefixed intentionally */
}
