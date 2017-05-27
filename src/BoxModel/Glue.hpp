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

		double size;
		double shrink;
		double stretch;

	public:
		Glue(int cardinality, double size, double shrink, double stretch)
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


		double getSize()
		{
			return size;
		}


		double getMinSize()
		{
			return size - shrink;
		}


		double getMaxSize()
		{
			if (cardinality > 0)
				return INT_MAX / 2;

			return size + stretch;
		}

		virtual double getActualSize() = 0;
		virtual void setActualSize(double size) = 0;

		virtual void dump(ostream &out, int level = 0) = 0;
		virtual void writePSOutput(PS::Writer &writer) = 0;
	};
}
