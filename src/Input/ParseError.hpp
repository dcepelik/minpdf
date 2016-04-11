#pragma once

#include <exception>
#include <string>

using namespace std;


namespace Input
{
	class ParseError : public exception
	{
		const char *msg;

	public:
		ParseError(const char *msg);

		virtual const char *what() const throw();
	};
}
