#pragma once

#include <memory>

#include "DocumentModel/Document.hpp"
#include "PDF/Document.hpp"

using namespace std;


class Renderer
{
public:
	Renderer();

	void render(vector<shared_ptr<Box>> &boxes);
};
