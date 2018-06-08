#include <algorithm>
#include <vector>
#include <iostream>
#include "Map.h"

Map::Map(int size_x, int size_y) :
    size_x(size_x), size_y(size_y)
{
    int x, y;

    this->board = new Box*[size_y];
    for (y = 0; y != this->size_y; y += 1)
    {
	this->board[y] = new Box[size_x];
	for (x = 0; x != this->size_x; x += 1)
	    this->board[y][x] = Box();
    }
}

Map::~Map()
{
    int y;

    for (y = 0; y != this->size_y; y += 1)
	delete this->board[y];
    delete this->board;
}

bool 	Map::AddCharacter(int id)
{
    for (auto &character : this->characters)
    {
	if (character.GetId() == id)
	    return false;
    }
    this->characters.push_back(Character(id, *this));
    return true;
}

bool 	Map::RemoveCharacter(int id)
{
    std::vector<Character>::iterator it = this->characters.begin();
    while (it != this->characters.end())
    {
	if (it->GetId() == id)
	{
	    this->characters.erase(it);
	    return true;
	}
	++it;
    }
    return false;
}

void	    Map::UpdateCharacters(std::vector<int> const& clients)
{
    bool    here;

    std::vector<Character>::iterator it = this->characters.begin();
    while (it != this->characters.end())
    {
	here = false;
	for (const auto& client : clients)
	{
	    if (it->GetId() == client)
		here = true;
	}
	if (here == false)
	    it = this->characters.erase(it);
	else
	    ++it;
    }
}

bool 	Map::FillBoard(std::string &board_string)
{
    try
    {
	int x = 0, y = 0;
	std::string::iterator it = board_string.begin();

	++it;
	while (*it != ']')
	{
	    ++it;
	    while (*it != ']')
	    {
		++it;
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
		    this->board[y][x].SetFood(std::atoi(amount.c_str()));
		    if (*it == ',')
			++it;
		}
		x += 1;
		++it;
	    }
	    y += 1;
	    x = 0;
	    ++it;
	}
	return true;
    }
    catch (std::out_of_range &e)
    {
	std::cerr << "Can't parse board sent by the server." << std::endl;
	return false;
    }
}

bool 	Map::FillCharacters(std::string &board_string)
{
    try
    {
	std::string::iterator it = std::next(board_string.begin(), 4);

	++it;
	while (*it != ']')
	{
	    ++it;
	    std::string character_args;
	    while (*it != ']')
		character_args += *it;
	    Character new_character(character_args, *this);
	    bool here = false;
	    for (auto & character : this->characters)
	    {
		if (character.GetId() == new_character.GetId())
		{
		    character = new_character;
		    here = true;
		}
	    }
	    if (here == false)
		this->characters.push_back(new_character);
	    ++it;
	}
	return true;
    }
    catch (std::out_of_range &e)
    {
	this->characters.clear();
	return true;
    }
    catch (...)
    {
	std::cerr << "Can't parse characters sent by the server." << std::endl;
	return false;
    }
}

Box **Map::GetBoard() const
{
    return(board);
}

std::vector<Character> const&	Map::GetCharacters() const
{
    return (this->characters);
}

int Map::GetSizeX() const
{
    return (this->size_x);
}

int Map::GetSizeY() const
{
    return (this->size_y);
}

Map&	Map::operator=(Map const & other)
{
    int x = 0, y = 0;

    if (&other == this)
	return *this;
    // deleting previous table
    for (y = 0; y != this->size_y; y += 1)
	delete this->board[y];
    delete this->board;
    this->size_x = other.size_x;
    this->size_y = other.size_y;
    // filling new table
    this->board = new Box*[size_y];
    for (y = 0; y != this->size_y; y += 1)
    {
	this->board[y] = new Box[size_x];
	for (x = 0; x != this->size_x; x += 1)
	    this->board[y][x] = other.GetBoard()[y][x];
    }
    this->characters = other.characters;
    return *this;
}
