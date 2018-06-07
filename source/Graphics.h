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

		bool						ReceiveBoard(std::string & value);

  		std::map<std::string, bool (Graphics::*)(std::string &)> protocol = {
		    { "101", &Graphics::ReceiveBoard }
  		};
};

#endif /* GRAPHICS_H_ */
