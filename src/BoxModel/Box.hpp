#pragma once

#include <climits>
#include <iostream>
#include <memory>

#include "PS/Writer.hpp"
#include "Styles/Style.hpp"

using namespace Styles;
using namespace std;

namespace BoxModel
{
	class Box
	{
	protected:
		int width;
		int height;

		int badness = INT_MAX;		/* cost when breaking here */
		shared_ptr<Box> prev;		/* previous division point */

	public:
		Box(int width = 0, int height = 0);

		virtual void dump(ostream &out, int level = 0) = 0;
		virtual void writePSOutput(PS::Writer &writer) = 0;

		int getWidth();
		int getHeight();
		int getBadness();
		shared_ptr<Box> getPrev();

		void setWidth(int width);
		void setHeight(int height);
		void setBadness(int badness);
		void setPrev(shared_ptr<Box> prev);
	};
}
