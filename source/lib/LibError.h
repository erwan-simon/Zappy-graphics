#ifndef LIBERROR_H_
# define LIBERROR_H_

# include <exception>
# include <iostream>
# include <string>

class LibError {
    public:
        LibError(std::string const& message = "", int type = 0);
        virtual ~LibError() throw();

        virtual const char* what() const throw();

    private:
        std::string     message;
        int             type;
};

# endif /* LIBERROR_H_ */
