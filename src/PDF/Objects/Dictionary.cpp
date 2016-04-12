#include "Dictionary.hpp"
#include "Name.hpp"

using namespace PDF::Objects;
using namespace PDF;
using namespace std;


void
Dictionary::writePDFOutput(Writer &writer)
{
	writer.writeLine("<<");
	writer.increaseIndent();

	for (auto item: items) {
		Name(item.first).writePDFOutput(writer);
		writer.increaseIndent();
		item.second->writePDFOutput(writer);
		writer.decreaseIndent();
	}
	
	writer.decreaseIndent();
	writer.writeLine(">>");
}


void
Dictionary::addItem(string name, Object *obj)
{
	items.emplace(name, obj);
}
