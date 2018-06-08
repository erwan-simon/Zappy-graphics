#ifndef NETWORK_H_
# define NETWORK_H_

# include <vector>
# include <string>
# include <sys/socket.h>
# include <netinet/in.h>

class 					Network {
    public:
	Network(char *addr, int port);
	~Network();

	bool				ReadFromServer();
	bool 				SendMessage(std::string const & message);
	bool 				ReceiveMessage();
	std::vector<std::string> &	GetBuffer();
	void				ClearBuffer();

    private:
	int 				port;
	int 				sockfd;
	struct sockaddr_in 		serv_addr;
	struct hostent			*server;
	fd_set 				active_fd_set;
	std::vector<std::string>	buffer;
};

#endif /* NETWORK_H_ */
