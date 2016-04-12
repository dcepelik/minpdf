#include "Array.hpp"

using namespace PDF::Objects;
using namespace std;


void
Array::writePDFOutput(Writer &writer)
{
	writer.writeLine("[");
	writer.increaseIndent();

	for (auto child: children) {
		child->writePDFOutput(writer);
	}

	writer.decreaseIndent();
	writer.writeLine("]");
}


void
Array::addChild(Object *obj)
{
	children.push_back(obj);
}
