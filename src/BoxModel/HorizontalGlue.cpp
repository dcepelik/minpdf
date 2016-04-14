#include <iostream>

#include "HorizontalGlue.hpp"

using namespace BoxModel;


HorizontalGlue::HorizontalGlue() : Box(0, 0) {}


BoxType
HorizontalGlue::getType()
{
	return BoxType::HorizontalGlue;
}
