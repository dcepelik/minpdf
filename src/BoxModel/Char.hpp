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
		virtual int getStretchability();
		virtual int getWidth();
		virtual void dump();
		virtual void print(ostream &out) const;
	};
}
