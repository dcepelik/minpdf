#pragma once

#include "List.hpp"

using namespace std;


namespace BoxModel
{
	class HList : public List
	{
	protected:
		int getBoxSize(shared_ptr<Box> box)
		{
			return box->getWidth();
		}


		int getMaxListSize()
		{
			return maxSize; /* TODO */
		}


	public:
		HList(int maxSize) : List(maxSize)
		{
			this->height = 8;
		}


		void dump(ostream &out, int level)
		{
			out << string(level, '\t') << "<->[";
			
			for (auto child: children)
				child->dump(out, level + 1);

			out << ']' << endl;
		}


		void writePSOutput(PS::Writer &writer)
		{
			divideSpaces();

			List::writePSOutput(writer);
			writer.writeTd(-getMaxListSize(), -height); /* TODO */
		}
	};
}
