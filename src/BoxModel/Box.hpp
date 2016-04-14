#pragma once

#include <iostream>

#include "BoxType.hpp"

using namespace std;

namespace BoxModel
{
	class Box
	{
		int originX;
		int originY;
		int width;
		int height;

	public:
		Box(int width, int height);

		void setOrigin(int originX, int originY);

		virtual BoxType getType() = 0;

		int getWidth();
		int getHeight();

		void setWidth(int width);
	};
}
