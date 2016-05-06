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

		int badness = 1e4;		/* cost when breaking here */
		shared_ptr<Box> prev;		/* previous division point */

	public:
		Box(int width = 0, int height = 0)
		{
			this->width = width;
			this->height = height;
		}


		virtual void dump(ostream &out, int level = 0) = 0;
		virtual void writePSOutput(PS::Writer &writer) = 0;


		int getWidth()
		{
			return width;
		}

		int getHeight()
		{
			return height;
		}

		int getBadness()
		{
			return badness;
		}

		shared_ptr<Box> getPrev()
		{
			return prev;
		}

		void setWidth(int width)
		{
			this->width = width;
		}

		void setHeight(int height)
		{
			this->height = height;
		}

		void setBadness(int badness)
		{
			this->badness = badness;
		}

		void setPrev(shared_ptr<Box> prev)
		{
			this->prev = prev;
		}
	};
}
