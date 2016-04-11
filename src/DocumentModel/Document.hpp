#pragma once

#include <memory>
#include <vector>

#include "Elements/Container.hpp"

namespace DocumentModel
{
	class Document : public Container
	{
	public:
		Document();
		void expand();
	};
}
