#pragma once

#include "Box.hpp"


namespace BoxModel
{
	class HorizontalGlue : public Box
	{
		int width;

	public:
		void setWidth(int width);
		virtual int getStretchability();
		virtual int getWidth();
		virtual void dump();
		virtual void print(ostream &out) const;
	};
}
