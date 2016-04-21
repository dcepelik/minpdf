#pragma once

#include <memory>
#include <vector>

#include "Elements/Container.hpp"
#include "Styles/StyleTable.hpp"

using namespace Styles;


namespace DocumentModel
{
	class Document : public Elements::Container
	{
		shared_ptr<StyleTable> styleTable;

	public:
		Document();

		void setStyleTable(shared_ptr<StyleTable> styleTable);

		shared_ptr<StyleTable> getStyleTable();
	};
}
