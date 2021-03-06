#ifndef GRAPHICS_H_
# define GRAPHICS_H_

# include <map>
# include "Map.h"
# include "Network.h"
# include "MyNcurses.h"

class				    Graphics {
    public:
	Graphics(int port, char *addr);
	~Graphics();

	bool 			    Play();

    private:
	Network			    network;
	MyNcurses 		    ncurse;
	std::string		    **board;
	std::vector<std::string>    characters;
	Map 			    *map = NULL;

	bool 			    ParseArguments(std::string &argument);
	void			    DrawBoard();
	bool		 	    AskForUpdate();

	bool			    Ok(std::string & value);
	bool			    Error(std::string & value);
	bool			    Exit(std::string & value);
	bool			    ServerWelcome(std::string & value);
	bool			    ReceiveBoard(std::string & value);
	bool			    ReceiveInventory(std::string & value);
	bool			    ReceiveCharacters(std::string & value);

	std::map<std::string, bool (Graphics::*)(std::string &)> protocol = {
	    { "001", &Graphics::Ok },
	    { "002", &Graphics::Error },
	    { "003", &Graphics::Exit },
	    { "100", &Graphics::ServerWelcome },
	    { "101", &Graphics::ReceiveBoard },
	    { "103", &Graphics::ReceiveInventory },
	    { "104", &Graphics::ReceiveCharacters }
	};
};

#endif /* GRAPHICS_H_ */
