#include "Error.h"

Error::Error(std::string const& message) :
   message(message)
{
}

Error::~Error() throw()
{
}

const char*     Error::what() const throw()
{
    return this->message.c_str();
}
