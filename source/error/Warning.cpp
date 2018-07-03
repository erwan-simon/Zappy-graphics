#include "Warning.h"

Warning::Warning(std::string const& message) :
   message(message)
{
}

Warning::~Warning() throw()
{
}

const char*     Warning::what() const throw()
{
    return this->message.c_str();
}
