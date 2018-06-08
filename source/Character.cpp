#include "Map.h"
#include "Character.h"

Character::Character(int id, Map &map) :
    id(id), map(map)
{
}

int Character::GetId() const
{
    return (this->id);
}

const int*	Character::GetLocation() const
{
    return (this->location);
}

void 	Character::Setlocation(int x, int y)
{
    location[0] = x;
    location[1] = y;
}

void 	Character::AddFood(int foodNb)
{
    this->food += foodNb;
}

bool 	Character::ConsumeFood()
{
    if (food == 0)
	    return false;
    food -= 1;
    return true;
}

Character &	Character::operator=(Character const &other)
{
    if (&other == this)
	    return (*this);
    this->id = other.id;
    this->map = other.map;
    this->location[0] = other.location[0];
    this->location[1] = other.location[1];
    this->food = other.food;
    return *this;
}

Character::~Character()
{
}
