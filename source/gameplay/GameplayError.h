#ifndef GAMEPLAYERROR_H_
# define GAMEPLAYERROR_H_

# include <exception>
# include <iostream>
# include <string>

class GameplayError {
    public:
        GameplayError(std::string const& message = "", int type = 0);
        virtual ~GameplayError() throw();

        virtual const char* what() const throw();

    private:
        std::string     message;
        int             type;
};

# endif /* GAMEPLAYERROR_H_ */
