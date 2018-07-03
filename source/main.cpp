#include <cstdio>
#include <iostream>
#include "Graphics.h"
#include "Error.h"

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
    } catch (Error &e)
    {
	std::cerr << "Error: " << e.what() << std::endl;
	return 1;
    }
    return 0;
}
