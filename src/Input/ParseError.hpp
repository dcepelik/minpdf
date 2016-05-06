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
		ParseError(const char *msg)
		{
			this->msg = msg;
		}


		const char *what() const throw()
		{
			return msg;
		}
	};
}
