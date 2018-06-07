NAME	= graphics

CC	= g++

RM	= rm -f

SRCS	= ./source/main.cpp		\
		  ./source/Network.cpp	\
		  ./source/MyNcurses.cpp\
		  ./source/Graphics.cpp

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS += -W -Wall -Wextra -g3 -std=c++11

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) -lncurses

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
