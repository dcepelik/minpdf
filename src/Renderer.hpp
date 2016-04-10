#pragma once

#include <memory>

#include "Document.hpp"
#include "PDF/Document.hpp"

using namespace std;


class Renderer
{
	vector<shared_ptr<Box>> boxes;

	void typesetBoxes();

public:
	Renderer();
	void formatLine(vector<shared_ptr<Box>>::iterator begin,
		vector<shared_ptr<Box>>::iterator end, int y);
	shared_ptr<PDF::Document> render(shared_ptr<Element> doc);
};
