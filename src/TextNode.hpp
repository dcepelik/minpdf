#pragma once

#include <string>


using namespace std;


class TextNode : public Element
{
	string text;

public:
	TextNode(string text);
	void dump(int level = 0);
	virtual bool empty();
};
