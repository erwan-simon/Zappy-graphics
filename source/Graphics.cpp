#include <iostream>
#include <cctype>
#include <string>
#include <chrono>
#include <thread>
#include "Network.h"
#include "Graphics.h"
#include "Map.h"
#include "MyNcurses.h"

Graphics::Graphics(int port, char *addr) :
    network(addr, port)
{
    ;
    // Get the size of the board
    if (this->network.SendMessage(std::string("300\n")) == false ||
	    this->network.ReadFromServer(true) == false ||
	    this->network.GetBuffer().size() == 0 ||
	    this->ServerWelcome(*(this->network.GetBuffer().begin())) == false ||
	    this->map == NULL)
    {
        this->network.SendMessage(std::string("003 Got an error need to shut down.\n"));
	throw std::string("Can't get the map size from the server");
    }
    this->network.ClearBuffer();
    this->ncurse.OpenWindow(this->map->GetSizeX(), this->map->GetSizeY());
    // Get board
    if (network.SendMessage(std::string("301\n")) == false ||
	    this->network.ReadFromServer(true) == false ||
	    this->network.GetBuffer().size() == 0 ||
	    this->ReceiveBoard(*(this->network.GetBuffer().begin())) == false)
    {
        this->network.SendMessage(std::string("003 Got an error need to shut down.\n"));
	this->ncurse.CloseWindow();
	throw std::string("Can't get the board contents from the server");
    }
    this->network.ClearBuffer();
    // get characters
    if (network.SendMessage(std::string("302\n")) == false ||
	    this->network.ReadFromServer(true) == false ||
	    this->network.GetBuffer().size() == 0 ||
	    this->ReceiveCharacters(*(this->network.GetBuffer().begin())) == false)
    {
        this->network.SendMessage(std::string("003 Got an error need to shut down.\n"));
	this->ncurse.CloseWindow();
	throw std::string("Can't get the characters from the server");
    }
    this->network.ClearBuffer();
}

bool 	Graphics::Play()
{
    while (1)
    {
	// std::this_thread::sleep_for(std::chrono::milliseconds(500));
	if (this->AskForUpdate() || this->network.ReadFromServer() == false)
	    break;
	if (this->network.GetBuffer().size() != 0)
	{
	    for (auto & message : this->network.GetBuffer())
		this->ParseArguments(message);
	    this->network.ClearBuffer();
	    this->DrawBoard();
	}
    }
    return true;
}

bool	Graphics::Ok(std::string &)
{
    return true;
}

bool	Graphics::Error(std::string & value)
{
    try {
	std::cerr << "Error: " << value.substr(4) << std::endl;
        throw value.substr(4);
    }
    catch (std::out_of_range& e)
    {
	throw std::string("Server send an error code without explaining why.");
    }
}

bool	Graphics::Exit(std::string & value)
{
    try {
	std::string message = std::string("Server disconnected ");
	message += value.substr(4);
	throw message;
    }
    catch (std::out_of_range& e)
    {
	throw std::string("Server disconnected itself.");
    }
}

bool	Graphics::ServerWelcome(std::string & value)
{
    std::cout << "Server accepted connection !" << std::endl;
    try {
	// Get map size
	std::string sizeX;
	std::string sizeY;

	std::string::iterator it = std::next(value.begin(), 4);
	while (*it != ' ' && it != value.end())
	{
	    if (!isdigit(*it))
	    {
		std::cerr << "Can't obtain map size from server welcome message" << std::endl;
		return false;
	    }
	    sizeX += *it;
	    ++it;
	}
	++it;
	while (it != value.end())
	{
	    if (!isdigit(*it))
	    {
		std::cout << *it << std::endl;
		std::cerr << "Can't obtain map size from server welcome message" << std::endl;
		return false;
	    }
	    sizeY += *it;
	    ++it;
	}
	this->map = new Map(std::atoi(sizeX.c_str()), std::atoi(sizeY.c_str()));
    }
    catch (std::out_of_range &e)
    {
	std::cerr << "Can't obtain map size from server welcome message" << std::endl;
	return false;
    }
    return true;
}

bool			    Graphics::ReceiveBoard(std::string &argument)
{
    std::string::iterator   it = std::next(argument.begin(), 4);
    int			    level = 0;

    while (*it == '[')
    {
	if (*it == '[')
	{
	    level += 1;
	    ++it;
	}
    }
    if (level != 3)
    {
	std::cerr << "Wrong level in the sent board" << std::endl;
	return false;
    }
    this->map->FillBoard(argument);
    return true;
}

bool	Graphics::ReceiveInventory(std::string &)
{
    return true;
}

bool	Graphics::ParseArguments(std::string &argument)
{
    try {
	if (this->protocol.find(argument.substr(0, 3)) != this->protocol.end())
	    return ((this->*protocol[argument.substr(0, 3)])(argument));
	else
	{
	    std::cerr << argument.substr(0, 3) << ": protocol unknown." << std::endl;
	    return false;
	}
    }
    catch (std::out_of_range& e)
    {
	std::cerr << argument << "\nNo protocol number found..." << std::endl;
	return false;
    }
}

bool    Graphics::ReceiveCharacters(std::string &argument)
{
    std::string::iterator   it = std::next(argument.begin(), 4);
    int			    level = 0;
    while (*it == '[')
    {
	if (*it == '[')
	{
	    level += 1;
	    ++it;
	}
    }
    if (level < 1)
    {
	std::cerr << "Wrong level in the sent board" << std::endl;
	return false;
    }
    return (this->map->FillCharacters(argument));
}


void 	Graphics::DrawBoard()
{
    Box **board_copy = this->map->GetBoard();

    for (int y = 0; y != this->map->GetSizeY(); y += 1)
    {
	for (int x = 0; x != this->map->GetSizeX(); x += 1)
	{
	    bool done = false;
	    for (const auto &character : this->map->GetCharacters())
	    {
		if (character.GetLocation()[0] == x && character.GetLocation()[1] == y)
		{
		    this->ncurse.BuildCell(x, y, MyNcurses::E_BLUE);
		    done = true;
		}
	    }
	    if (done == true)
		continue;
	    else if (board_copy[y][x].GetFood() != 0)
		this->ncurse.BuildCell(x, y, MyNcurses::E_RED);
	    else
		this->ncurse.BuildCell(x, y, MyNcurses::E_BLACK);
	}
    }
    this->ncurse.RefreshWindow();
}

bool 	Graphics::AskForUpdate()
{
    return (this->network.SendMessage(std::string("301")) &&
	    this->network.SendMessage(std::string("302")));
}

Graphics::~Graphics()
{
    this->ncurse.ClearWindow();
    this->ncurse.CloseWindow();
    this->network.SendMessage(std::string("003\n"));
}
