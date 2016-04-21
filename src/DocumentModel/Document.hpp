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
		Document();

		void setStyleTable(shared_ptr<StyleTable> styleTable);

		shared_ptr<StyleTable> getStyleTable();

		void renderPDFOutput(ostream &out);
	};
}
