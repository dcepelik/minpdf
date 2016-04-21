#pragma once

#include "List.hpp"

using namespace std;


namespace BoxModel
{
	class HList : public List
	{
	protected:
		int getBoxSize(shared_ptr<Box> el);
		int getMaxListSize();

	public:
		HList(int size);

		void dump(ostream &out, int level = 0);
		void writePSOutput(PS::Writer &writer);
	};
}
