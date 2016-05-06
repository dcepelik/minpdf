#pragma once

#include <string>

#include "Object.hpp"
#include "Dictionary.hpp"
#include "Number.hpp"


using namespace PDF;
using namespace std;


namespace PDF
{
	namespace Objects
	{
		class Stream : public Object
		{
			string content;

		public:
			Stream()
			{
			}


			Stream(string content)
			{
				this->content = content;
			}


			void writePDFOutput(Writer &writer)
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
		};
	}
}
