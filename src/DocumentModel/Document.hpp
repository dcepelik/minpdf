#pragma once

#include <memory>
#include <vector>

#include "Elements/Container.hpp"

using namespace DocumentModel::Elements;


namespace DocumentModel
{
	class Document : public Container
	{
	public:
		Document();
		void expand();
	};
}
