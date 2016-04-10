#pragma once

#include <iostream>

using namespace std;

class Box
{
protected:
	int x;
	int y;
	int width;

public:
	void setOrigin(int x, int y);
	virtual int getStretchability() = 0;
	virtual int getWidth() = 0;
	void setWidth(int width);
	virtual void dump() = 0;
	virtual void print(ostream &out) const = 0;
};
