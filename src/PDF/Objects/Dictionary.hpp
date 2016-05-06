#pragma once

#include <memory>
#include <unordered_map>

#include "Name.hpp"
#include "Object.hpp"

using namespace PDF;
using namespace std;


namespace PDF
{
	namespace Objects
	{
		class Dictionary : public Object
		{
			unordered_map<string, Object *> items;

		public:
			void writePDFOutput(Writer &writer)
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


			void addItem(string name, Object *obj)
			{
				items.emplace(name, obj);
			}
		};
	}
}
