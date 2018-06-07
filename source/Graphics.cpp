#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "Network.h"
#include "Graphics.h"



Graphics::Graphics(int port, char *addr) :
	network(addr, port)
{
	network.SendMessage(std::string("300\n"));
}

bool 	Graphics::Play()
{
	while (1)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		if (this->network.ReadFromServer() == false)
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

bool						Graphics::Ok(std::string &)
{
	return true;
}

bool						Graphics::Error(std::string & value)
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

bool						Graphics::Exit(std::string & value)
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

bool						Graphics::ServerWelcome(std::string & value)
{
	try {
		std::cout << "Server accepted connection : " << value.substr(4) << std::endl;
	}
	catch (std::out_of_range &e)
	{
		std::cout << "Server accepted connection !" << std::endl;
	}
	this->network.SendMessage("301\n");
	return true;
}

bool 						Graphics::ReceiveBoard(std::string &argument)
{
	std::string::iterator 	it = std::next(argument.begin(), 5);
	int 					level = 0;

	while (*it == '[')
	{
		if (*it == '[')
		{
			level += 1;
			++it;
		}
	}
	if (level != 3)
		return false;
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

}

void 	Graphics::AskForUpdate()
{
	this->network.SendMessage(std::string("301"));
}

Graphics::~Graphics()
{
	network.SendMessage(std::string("3\n"));
}
