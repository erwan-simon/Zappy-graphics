#ifndef ERROR_H_
# define ERROR_H_

# include <exception>
# include <iostream>
# include <string>

class Error {
    public:
        Error(std::string const& message = "");
        virtual ~Error() throw();

        virtual const char* what() const throw();

    private:
        std::string     message;
};

# endif /* ERROR_H_ */
