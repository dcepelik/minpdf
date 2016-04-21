#pragma once

#include <vector>

#include "Box.hpp"

using namespace std;


namespace BoxModel
{
	class Container : public Box
	{
	protected:
		/* my software protects the children */
		vector<shared_ptr<Box>> children;

	public:
		Container();

		void addChild(shared_ptr<Box> child);

		virtual void dump(ostream &out, int level = 0);
		virtual void writePSOutput(PS::Writer &writer);
	};
}
