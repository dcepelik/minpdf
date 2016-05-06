#pragma once

#include <vector>
#include <memory>

#include "Object.hpp"

using namespace std;


namespace PDF
{
	namespace Objects
	{
		class Array : public Object
		{
			vector<Object *> children;

		public:
			void writePDFOutput(Writer &writer)
			{
				writer.writeLine("[");
				writer.increaseIndent();

				for (auto child: children) {
					child->writePDFOutput(writer);
				}

				writer.decreaseIndent();
				writer.writeLine("]");
			}


			void addChild(Object *obj)
			{
				children.push_back(obj);
			}
		};
	}

}
