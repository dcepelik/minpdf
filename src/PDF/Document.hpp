#pragma once

#include <vector>
#include <memory>

#include "Page.hpp"

using namespace std;


namespace PDF
{
	class Document
	{
		vector<shared_ptr<Page>> objects;
	};
}
