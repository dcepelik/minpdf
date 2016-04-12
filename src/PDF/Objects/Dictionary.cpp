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
Dictionary::addItem(string key, shared_ptr<Object> value)
{
	items.emplace(key, value);
}


void
Dictionary::addItem(string key, Object *value)
{
	items.emplace(key, shared_ptr<Object>(value));
}
