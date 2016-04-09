#pragma once


#include <memory>
#include <vector>

#include "Container.hpp"


class Document : public Container
{
public:
	Document();
	void expand();
};
