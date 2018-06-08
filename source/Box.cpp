#include "Box.h"

Box::Box()
{

}

int 	Box::GetFood() const
{
    return (food);
}

void 	Box::SetFood(int food)
{
    this->food = food;
}

Box::~Box()
{
}
