#pragma once

#include "List.hpp"

using namespace std;


namespace BoxModel
{
	class VList : public List
	{
	protected:
		int getBoxSize(shared_ptr<Box> box);
		int getMaxListSize();

	public:
		VList(int size);

		void dump(ostream &out, int level = 0);
		void writePSOutput(PS::Writer &writer);
	};
}
