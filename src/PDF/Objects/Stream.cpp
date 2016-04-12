#include "Stream.hpp"
#include "Dictionary.hpp"
#include "Number.hpp"

using namespace PDF::Objects;
using namespace PDF;
using namespace std;


Stream::Stream()
{
}


Stream::Stream(string content)
{
	this->content = content;
}


void
Stream::writePDFOutput(Writer &writer)
{
	Dictionary dict;
	dict.addItem("Length", new Number(content.length()));

	dict.writePDFOutput(writer);
	writer.increaseIndent();
	writer.writeLine("stream");
	writer.write(content);
	writer.writeLine("endstream");
	writer.decreaseIndent();
}
