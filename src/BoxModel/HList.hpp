#pragma once

#include <vector>

#include "Box.hpp"

namespace BoxModel
{
	class HList : public Box
	{
		vector<shared_ptr<Box>> items;

	public:
		BoxType getType();
		void writePSOutput(ostream &out);
		void dump();

		void addItem(shared_ptr<Box> item);
	};
}
