NAME		=   graphics

CC		=   g++

RM		=   rm -f

ERROR_SRCS	=   ./source/error/Error.cpp	\
		    ./source/error/Warning.cpp
ERROR_INCLUDE	=   -I ./source/error/

LIB_SRCS	=   ./source/lib/MyNcurses.cpp
LIB_INCLUDE	=   -I ./source/lib

GAMEPLAY_SRCS   =   ./source/gameplay/Map.cpp	    \
		    ./source/gameplay/Box.cpp	    \
		    ./source/gameplay/Character.cpp
GAMEPLAY_INCLUDE=   -I ./source/gameplay/

NETWORK_SRCS	=   ./source/network/Network.cpp
NETWORK_INCLUDE =   -I ./source/network/

MAIN_SRCS	=   ./source/main.cpp	   \
		    ./source/Graphics.cpp
MAIN_INCLUDE	=   -I ./source/

OBJS		=   $(ERROR_SRCS:.cpp=.o)	\
		    $(LIB_SRCS:.cpp=.o)		\
		    $(GAMEPLAY_SRCS:.cpp=.o)	\
		    $(NETWORK_SRCS:.cpp=.o)	\
		    $(MAIN_SRCS:.cpp=.o)

CPPFLAGS	+=  $(ERROR_INCLUDE)	\
		    $(LIB_INCLUDE)	\
		    $(GAMEPLAY_INCLUDE)	\
		    $(NETWORK_INCLUDE)	\
		    $(MAIN_INCLUDE)

CPPFLAGS	+=  -W -Wall -Wextra -g3 -std=c++11

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(INCLUDE) $(OBJS) -o $(NAME) -lncurses

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
