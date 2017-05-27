#pragma once

#include <cassert>
#include <memory>
#include <map>

#include "Style.hpp"

using namespace std;

namespace Styles
{
	class StyleTable
	{
		map<string, unique_ptr<Style>> styles;

	public:
		StyleTable()
		{
		}


		void addStyle(string name, unique_ptr<Style> style)
		{
			styles.emplace(name, move(style));
		}


		Style *getStyle(string name)
		{
			return styles[name].get();
		}
	};
}
