#pragma once

#include "Box.hpp"


namespace BoxModel
{
	class Penalty : Box
	{
		int value;

	public:
		Penalty(int value);
	};
}
