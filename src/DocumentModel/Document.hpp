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

	public:
		Document() : VWrappingContainer(shared_ptr<Element>(NULL), "document", 762)
		{
		}


		void setStyleTable(shared_ptr<StyleTable> styleTable)
		{
			this->styleTable = styleTable;
		}


		shared_ptr<StyleTable> getStyleTable()
		{
			return styleTable;
		}


		void renderPDFOutput(ostream &out);
	};
}
