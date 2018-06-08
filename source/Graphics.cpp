#include <iostream>
#include <cctype>
#include <string>
#include <chrono>
#include <thread>
#include "Network.h"
#include "Graphics.h"
#include "Map.h"


Graphics::Graphics(int port, char *addr) :
    network(addr, port)
{
    network.SendMessage(std::string("300\n"));
}

bool 	Graphics::Play()
{
    while (1)
    {
	this->AskForUpdate();
	// std::this_thread::sleep_for(std::chrono::milliseconds(500));
	if (this->network.ReadFromServer() == false)
	    break;
	if (this->network.GetBuffer().size() != 0)
	{
	    for (auto & message : this->network.GetBuffer())
		this->ParseArguments(message);
	    this->network.ClearBuffer();
	    if (map != NULL)
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
    }
    catch (std::out_of_range& e)
    {
	std::cerr << "Error: no message given..." << std::endl;
    }
    throw 4;
}

bool	Graphics::Exit(std::string & value)
{
    try {
	std::cerr << "Server disconnected itself: " << value.substr(4) << std::endl;
    }
    catch (std::out_of_range& e)
    {
	std::cerr << "Server disconnected itself." << std::endl;
    }
    throw 5;
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
    this->network.SendMessage("301\n");
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

void 	Graphics::DrawBoard()
{
    Box **board_copy = this->map->GetBoard();

    for (int y = 0; y != this->map->GetSizeY(); y += 1)
    {
	for (int x = 0; x != this->map->GetSizeX(); x += 1)
	{
	    if (board_copy[y][x].GetFood() != 0)
	    {
		this->ncurse.BuildCell(x, y, MyNcurses::E_RED);
	    }
	}
    }
}

bool 	Graphics::AskForUpdate()
{
    return (this->network.SendMessage(std::string("301")));
}

Graphics::~Graphics()
{
    network.SendMessage(std::string("3\n"));
}
