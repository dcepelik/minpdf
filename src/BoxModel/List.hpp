#pragma once

#include <vector>

#include "Container.hpp"

namespace BoxModel
{
	class List : public Container
	{
	protected:
		double maxSize;


		List(double maxSize) : Container()
		{
			this->maxSize = maxSize;
		}

		void divideSpaces();

		virtual double getBoxSize(shared_ptr<Box> box) = 0;
	};
}
