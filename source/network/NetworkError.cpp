#include "NetworkError.h"

NetworkError::NetworkError(std::string const& message, int type) :
   message(message), type(type)
{
}

NetworkError::~NetworkError() throw()
{
}

const char*     NetworkError::what() const throw()
{
    return this->message.c_str();
}
