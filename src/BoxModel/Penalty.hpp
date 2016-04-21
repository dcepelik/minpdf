#pragma once

#include "Box.hpp"


namespace BoxModel
{
	class Penalty : public Box
	{
		int value;

	public:
		Penalty(int value);
	};
}
