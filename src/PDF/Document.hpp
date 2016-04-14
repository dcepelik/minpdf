#pragma once

#include <memory>
#include <vector>

#include "Objects/Array.hpp"
#include "Objects/Dictionary.hpp"
#include "Objects/IndirectObject.hpp"
#include "Objects/Literal.hpp"
#include "Objects/Name.hpp"
#include "Objects/Number.hpp"
#include "Objects/Stream.hpp"
#include "Page.hpp"
#include "Writer.hpp"

using namespace PDF::Objects;
using namespace PDF;
using namespace std;


namespace PDF
{
	class Document
	{
		vector<shared_ptr<Page>> docPages;

	public:
		Document();

		void addPage(shared_ptr<Page> page);

		void writePDFOutput(Writer &writer);
	};
}
