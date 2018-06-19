#include "LibError.h"

LibError::LibError(std::string const& message, int type) :
   message(message), type(type)
{
}

LibError::~LibError() throw()
{
}

const char*     LibError::what() const throw()
{
    return this->message.c_str();
}
