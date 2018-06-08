#include <cstdio>
#include <iostream>
#include "Graphics.h"

int main(int argc, char *argv[])
{
    if (argc != 3 || std::atoi(argv[2]) <= 0)
    {
	std::cerr << "Need to give the address then the port of the server" << std::endl;
	return 1;
    }
    try {
	Graphics graphics(std::atoi(argv[2]), argv[1]);
	graphics.Play();
    } catch (std::string e)
    {
	std::cerr << "Error: " << e << std::endl;
	return 1;
    }
    return 0;
}
