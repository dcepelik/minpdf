#pragma once

#include <climits>
#include <iostream>

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
		Glue(int cardinality, int size, int shrink, int stretch)
		{
			this->cardinality = cardinality;
			this->size = size;
			this->shrink = shrink;
			this->stretch = stretch;
		}


		int getCardinality()
		{
			return cardinality;
		}


		int getSize()
		{
			return size;
		}


		int getMinSize()
		{
			return size - shrink;
		}


		int getMaxSize()
		{
			if (cardinality > 0)
				return INT_MAX / 2;

			return size + stretch;
		}

		virtual int getActualSize() = 0;
		virtual void setActualSize(int size) = 0;

		virtual void dump(ostream &out, int level = 0) = 0;
		virtual void writePSOutput(PS::Writer &writer) = 0;
	};
}
