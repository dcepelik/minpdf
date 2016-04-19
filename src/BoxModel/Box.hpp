#pragma once

#include <iostream>
#include <memory>

#include "BoxType.hpp"

using namespace std;

namespace BoxModel
{
	class Box
	{
	protected:
		int originX;
		int originY;
		int width = 0;
		int height;
		int badness = 1e8;
		shared_ptr<Box> prev;

	public:
		Box(int width, int height);

		void setOrigin(int originX, int originY);

		virtual BoxType getType() = 0;
		virtual void writePSOutput(ostream &out) = 0;
		virtual void dump() = 0;

		int getWidth();
		int getHeight();

		int getBadness();
		void setBadness(int badness);

		shared_ptr<Box> getPrev();
		void setPrev(shared_ptr<Box> prev);

		void setWidth(int width);
	};
}
