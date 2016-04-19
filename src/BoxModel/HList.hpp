#pragma once

#include <vector>

#include "Container.hpp"

namespace BoxModel
{
	class HList : public Container
	{
		vector<shared_ptr<Box>> items;

	public:
		HList();

		BoxType getType();
		void writePSOutput(ostream &out);
		void dump();

		void addItem(shared_ptr<Box> item);
	};
}
