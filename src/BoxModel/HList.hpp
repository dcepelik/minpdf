#pragma once

#include "List.hpp"

using namespace std;


namespace BoxModel
{
	class HList : public List
	{
	protected:
		double getBoxSize(shared_ptr<Box> box)
		{
			return box->getWidth();
		}


		double getMaxListSize()
		{
			return maxSize; /* TODO */
		}


	public:
		HList(int maxSize) : List(maxSize)
		{
			this->height = 0;
		}


		virtual double getWidth()
		{
			return maxSize;
		}


		virtual double getHeight()
		{
			double maxHeight = 0;
			for (auto child: children) {
				maxHeight = max(maxHeight, child->getHeight());
			}

			return maxHeight;
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
			writer.writeTd(-getMaxListSize(), -getHeight());
		}
	};
}
