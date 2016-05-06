#pragma once

#include "List.hpp"

using namespace std;


namespace BoxModel
{
	class VList : public List
	{
	protected:
		int getBoxSize(shared_ptr<Box> box)
		{
			return box->getHeight();
		}


		int getMaxListSize()
		{
			return maxSize;
		}


	public:
		VList(int size) : List(size)
		{
		}


		void dump(ostream &out, int level)
		{
			out << string(level, '\t') << "^^[" << endl;

			for (auto child: children)
				child->dump(out, level + 1);

			out << string(level, '\t') << ']' << endl;
		}


		void writePSOutput(PS::Writer &writer)
		{
			divideSpaces();

			List::writePSOutput(writer);
			writer.writeTd(-612, -getMaxListSize());
		}
	};
}
