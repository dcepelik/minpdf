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
		Container() : Box(0, 0)
		{
		}


		void addChild(shared_ptr<Box> child)
		{
			children.push_back(child);
		}


		void prependChild(shared_ptr<Box> child)
		{
			children.insert(children.begin(), child);
		}


		void prependChildren(vector<shared_ptr<Box>> &children)
		{
			this->children.insert(this->children.begin(), children.begin(), children.end());
		}


		void dump(ostream &out, int level)
		{
			out << string('\t', level) << '{';

			for (auto child: children)
				child->dump(out, level + 1);

			out << string('\t', level) << '}';
		}


		void writePSOutput(PS::Writer &writer)
		{
			for (auto child: children)
				child->writePSOutput(writer);
		}
	};
}
