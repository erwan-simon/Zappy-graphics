#ifndef WARNING_H_
# define WARNING_H_

# include <exception>
# include <iostream>
# include <string>

class Warning {
    public:
        Warning(std::string const& message = "");
        virtual ~Warning() throw();

        virtual const char* what() const throw();

    private:
        std::string     message;
};

# endif /* WARNING_H_ */
