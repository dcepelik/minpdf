#pragma once

#include <vector>

#include "BoxModel/Box.hpp"

using namespace std;

namespace BoxModel
{
	class Container : public Box
	{
		vector<shared_ptr<Box>> children;

	public:
		Container();

		void addChild(shared_ptr<Box> child);

		void dump();
	};
}
