#pragma once

#include "Box.hpp"


namespace BoxModel
{
	class Glue : public Box
	{
	protected:
		int cardinality;

		int size;
		int shrink;
		int stretch;

	public:
		Glue(int cardinality, int size, int shrink, int stretch);

		int getCardinality();

		int getSize();
		int getMinSize();
		int getMaxSize();

		virtual int getActualSize() = 0;
		virtual void setActualSize(int size) = 0;

		virtual void dump(ostream &out, int level = 0) = 0;
		virtual void writePSOutput(PS::Writer &writer) = 0;
	};
}
