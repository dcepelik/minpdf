#pragma once

#include <memory>
#include <string>

using namespace std;


namespace PDF
{
	class Page
	{
		string code;

	public:
		Page(string code);
		string contents();
	};
}
