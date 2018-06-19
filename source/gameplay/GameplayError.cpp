#include "GameplayError.h"

GameplayError::GameplayError(std::string const& message, int type) :
   message(message), type(type)
{
}

GameplayError::~GameplayError() throw()
{
}

const char*     GameplayError::what() const throw()
{
    return this->message.c_str();
}
