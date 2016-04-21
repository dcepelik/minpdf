#include <climits>
#include <iostream>

#include "Glue.hpp"

using namespace BoxModel;


Glue::Glue(int cardinality, int size, int shrink, int stretch)
{
	this->cardinality = cardinality;
	this->size = size;
	this->shrink = shrink;
	this->stretch = stretch;
}


int
Glue::getCardinality()
{
	return cardinality;
}


int
Glue::getSize()
{
	return size;
}


int
Glue::getMinSize()
{
	return size - shrink;
}


int
Glue::getMaxSize()
{
	if (cardinality > 0)
		return INT_MAX;

	return size + stretch;
}
