#pragma once

#include "Box.hpp"

using namespace std;


namespace BoxModel
{
	class Char : public Box
	{
		char c;

	public:
		Char(char c);

		BoxType getType(); 
	};
}
