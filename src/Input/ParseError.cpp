#include "ParseError.hpp"

using namespace Input;


ParseError::ParseError(const char *msg)
{
	this->msg = msg;
}


const char *
ParseError::what() const throw()
{
	return msg;
}
