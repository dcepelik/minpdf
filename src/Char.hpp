#pragma once

#include "Box.hpp"


class Char : public Box
{
	char c;

public:
	Char(char c);
	virtual void dump();
};
