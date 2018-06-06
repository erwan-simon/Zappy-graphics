#include <string>
#include "Graphics.h"

Graphics::Graphics(int port, char *addr) :
	network(addr, port)
{
	network.SendMessage(std::string("300\n"));
}

bool						Graphics::ParseArguments(std::string &argument)
{
	std::string::iterator 	it = std::next(argument.begin(), 5);
	int 					level = 0;
	int 					protocol = 0;

	if (std::atoi(argument.substr(0, 3).c_str()) == 0)
		return false;
	else
		protocol = std::atoi(argument.substr(0, 3).c_str());
	while (*it == '[')
	{
		if (*it == '[')
		{
			level += 1;
			++it;
		}
	}
	if (level == 0)
		return false;
	while (level != 0)
	{
		level -= 1;
	}
	return true;
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
