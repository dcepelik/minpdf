#include "Box.hpp"

using namespace BoxModel;


Box::Box(int width, int height)
{
	this->width = width;
	this->height = height;
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


int
Box::getBadness()
{
	return badness;
}


shared_ptr<Box>
Box::getPrev()
{
	return prev;
}


void
Box::setWidth(int width)
{
	this->width = width;
}


void
Box::setHeight(int height)
{
	this->height = height;
}


void
Box::setBadness(int badness)
{
	this->badness = badness;
}


void
Box::setPrev(shared_ptr<Box> prev)
{
	this->prev = prev;
}

