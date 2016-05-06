#pragma once

#include "Box.hpp"


namespace BoxModel
{
	class Penalty : public Box
	{
		int value;

	public:
		Penalty(int value) : Box(0, 0)
		{
			this->value = value;
		}
	};
}
