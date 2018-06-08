#include "Map.h"
#include "Character.h"

Character::Character(int id, Map &map) :
    id(id), map(map)
{
}

Character::Character(std::string & args, Map &map) :
    map(map)
{
    std::string::iterator it = args.begin();
    this->id = -1;

    while (*it != ']')
    {
	std::string type;
	std::string amount;
	while (*it != ':')
	{
	    type += *it;
	    ++it;
	}
	++it;
	while (isdigit(*it))
	{
	    amount += *it;
	    ++it;
	}
	if (type == std::string("id"))
	{
	    if ((this->id = std::atoi(amount.c_str())) == false)
		throw std::string("Wrong ID for the new character");
	}
	else if (type == std::string("location_x"))
	{
	    if ((this->location[0] = std::atoi(amount.c_str())) == false)
		throw std::string("Wrong x location for the new character");
	}
	else if (type == std::string("location_y"))
	{
	    if ((this->location[1] = std::atoi(amount.c_str())) == false)
		throw std::string("Wrong y location for the new character");
	}
	else if (type == std::string("food"))
	{
	    if ((this->food = std::atoi(amount.c_str())) == false)
		throw std::string("Wrong food amount for the new character");
	}
	if (*it == ',')
	    ++it;
    }
    if (id < 0)
	throw std::string("No id were given in the new character creation");
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
