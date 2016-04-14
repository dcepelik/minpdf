#include "Box.hpp"

using namespace BoxModel;


Box::Box(int width, int height)
{
	this->width = width;
	this->height = height;
}


void
Box::setOrigin(int originX, int originY)
{
	this->originX = originX;
	this->originY = originY;
}


void
Box::setWidth(int width)
{
	this->width = width;
}

