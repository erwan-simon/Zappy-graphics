#ifndef NETWORKERROR_H_
# define NETWORKERROR_H_

# include <exception>
# include <iostream>
# include <string>

class NetworkError {
    public:
        NetworkError(std::string const& message = "", int type = 0);
        virtual ~NetworkError() throw();

        virtual const char* what() const throw();

    private:
        std::string     message;
        int             type;
};

# endif /* NETWORKERROR_H_ */
