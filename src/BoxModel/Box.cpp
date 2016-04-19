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


int
Box::getWidth()
{
	return width;
}


int
Box::getHeight()
{
	return height;
}


void
Box::setWidth(int width)
{
	this->width = width;
}


int
Box::getBadness()
{
	return badness;
}


void
Box::setBadness(int badness)
{
	this->badness = badness;
}


shared_ptr<Box>
Box::getPrev()
{
	return prev;
}


void
Box::setPrev(shared_ptr<Box> prev)
{
	this->prev = prev;
}


void
Box::writePSOutput(ostream &out)
{
	(void)out;
}
