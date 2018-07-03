#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include "Network.h"
#include "Error.h"

Network::Network(char *addr, int port) :
    port(port)
{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
	throw Error(strerror(errno));
    server = gethostbyname(addr);
    if (server == NULL) {
	fprintf(stderr,"ERROR, no such host\n");
	exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
      (char *)&serv_addr.sin_addr.s_addr,
      server->h_length);
    serv_addr.sin_port = htons(port);
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	throw Error(strerror(errno));
    FD_ZERO(&active_fd_set);
    FD_SET(sockfd, &active_fd_set);
}

bool	Network::SendMessage(std::string const & message)
{
    int	return_value = 0;

    if (message.back() == '\n')
	return_value = dprintf(sockfd, "%s", message.c_str());
    else
	return_value = dprintf(sockfd, "%s\n", message.c_str());
    if (return_value < 0)
    {
	std::cerr << "Couldn't send message to the server." << std::endl;
	return false;
    }
    return true;
}

bool		Network::ReceiveMessage()
{

    char	buffer;
    int		nbytes;
    std::string	message;

    while (true)
    {
	nbytes = read(sockfd, &buffer, 1);
	if (nbytes < 0)
            throw Error(strerror(errno));
	else if (nbytes == 0)
	{
	    /* End-of-file. */
	    std::cerr << "Server disconnected" << std::endl;
	    return false;
	}
	else
	{
	    if (buffer == '\n')
		break;
	    /* Data read. */
	    message += buffer;
	}
    }
    this->buffer.push_back(message);
    return true;
}

bool		    Network::ReadFromServer(bool blocking)
{
    fd_set	    read_fd_set;
    int		    i;
    struct timeval  tv = {0, 50};

    /* Block until input arrives on one or more active sockets. */
    read_fd_set = active_fd_set;
    if (blocking)
    {
	if (select(FD_SETSIZE, &read_fd_set, NULL, NULL, NULL) < 0)
            throw Error(strerror(errno));
    }
    else
    {
	if (select(FD_SETSIZE, &read_fd_set, NULL, NULL, &tv) < 0)
            throw Error(strerror(errno));
    }
    /* Service all the sockets with input pending. */
    for (i = 0; i < FD_SETSIZE; ++i)
    {
	if (FD_ISSET (i, &read_fd_set))
	{
	    if (i == sockfd)
	    {
		return(this->ReceiveMessage() == true);
	    }
	    else
	    {
		std::cerr << "else" << std::endl;
		/* Data arriving on an already-connected socket. */
		return (this->ReceiveMessage() == true);
	    }
	}
    }
    return true;
}

std::vector<std::string> &	Network::GetBuffer()
{
    return (this->buffer);
}

void	Network::ClearBuffer()
{
    this->buffer.clear();
}

Network::~Network()
{
    close(sockfd);
}
