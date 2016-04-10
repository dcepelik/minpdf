#pragma once

#include <vector>
#include <memory>

#include "Objects/Array.hpp"
#include "Objects/Dictionary.hpp"
#include "Objects/IndirectObject.hpp"
#include "Objects/Name.hpp"
#include "Objects/Number.hpp"
#include "Objects/Stream.hpp"
#include "Page.hpp"

using namespace PDF;
using namespace PDF::Objects;
using namespace std;


namespace PDF
{
	class Document
	{
		vector<shared_ptr<Page>> pages;

		IndirectObject<Dictionary> catalog;
		IndirectObject<Dictionary> pageCatalog;
		Array pageRefs;
		vector<shared_ptr<IndirectObject<Dictionary>>> pageDefs;
		vector<shared_ptr<IndirectObject<Stream>>> pageStreams;
		Dictionary trailer;

		void preparePDFObjects();
		void printObjAndPushXref(ostream &out, Object &obj,
			vector<int> &xref);
	
	public:
		Document();

		void addPage(shared_ptr<Page> page);
		void print(ostream &out);
	};
}
