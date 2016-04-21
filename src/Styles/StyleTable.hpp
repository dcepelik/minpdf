#pragma once

#include <map>

#include "Style.hpp"

using namespace std;

namespace Styles
{
	class StyleTable
	{
		map<string, shared_ptr<Style>> styles;

	public:
		StyleTable();

		void addStyle(string name, shared_ptr<Style> style);

		shared_ptr<Style> getStyle(string name);
	};
}
