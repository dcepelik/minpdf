#pragma once

#include "Box.hpp"


namespace BoxModel
{
	class HorizontalGlue : public Box
	{
	public:
		HorizontalGlue();

		BoxType getType(); 
	};
}
