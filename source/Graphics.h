#ifndef GRAPHICS_H_
# define GRAPHICS_H_

# include "Network.h"

class 				Graphics {
	public:
		Graphics(int port, char *addr);
		~Graphics();

	private:
		bool 		ParseArguments(std::string &argument);
		void		DrawBoard();
		void 		AskForUpdate();
		Network		network;
		MyNcurses 	ncurse;
};

#endif /* GRAPHICS_H_ */
