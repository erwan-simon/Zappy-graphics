#ifndef GRAPHICS_H_
# define GRAPHICS_H_

# include <map>
# include "Network.h"
# include "MyNcurses.h"

class 								Graphics {
	public:
		Graphics(int port, char *addr);
		~Graphics();

		bool 						Play();

	private:
		Network						network;
		MyNcurses 					ncurse;
		std::string 				**board;
		std::vector<std::string>	characters;
		bool 						ParseArguments(std::string &argument);
		void						DrawBoard();
		void 						AskForUpdate();

		bool						Ok(std::string & value);
		bool						Error(std::string & value);
		bool						Exit(std::string & value);
		bool						ServerWelcome(std::string & value);
		bool						ReceiveBoard(std::string & value);
		bool						ReceiveInventory(std::string & value);

  		std::map<std::string, bool (Graphics::*)(std::string &)> protocol = {
			{ "001", &Graphics::Ok },
			{ "002", &Graphics::Error },
			{ "003", &Graphics::Exit },
			{ "100", &Graphics::ServerWelcome },
		    { "101", &Graphics::ReceiveBoard },
  			{ "103", &Graphics::ReceiveInventory },
		};
};

#endif /* GRAPHICS_H_ */
