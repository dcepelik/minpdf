#pragma once

#include <memory>
#include <vector>

#include "Elements/VWrappingContainer.hpp"
#include "Styles/StyleTable.hpp"

using namespace DocumentModel::Elements;
using namespace Styles;


namespace DocumentModel
{
	class Document : public VWrappingContainer
	{
		shared_ptr<StyleTable> styleTable;

		int pageWidth = 594;
		int pageHeight = 842;
		int contentWidth = pageWidth - 194;
		string filename;

		void prerender(vector<shared_ptr<Box>> &boxes);

	public:
		Document() : VWrappingContainer(shared_ptr<Element>(NULL), "document", (842.25 - 300)) /* TODO */
		{
		}


		void setStyleTable(shared_ptr<StyleTable> styleTable)
		{
			this->styleTable = styleTable;
		}


		int getContentWidth()
		{
			return this->contentWidth;
		}


		string getFilename()
		{
			return filename;
		}


		void setFilename(string filename)
		{
			this->filename = filename;
		}


		shared_ptr<StyleTable> getStyleTable()
		{
			return styleTable;
		}


		void renderPDFOutput(ostream &out);
	};
}
