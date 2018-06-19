NAME		=   graphics

CC		=   g++

RM		=   rm -f

LIB_SRCS	=   ./source/lib/MyNcurses.cpp	\
		    ./source/lib/LibError.cpp
LIB_INCLUDE	=   -I ./source/lib

GAMEPLAY_SRCS   =   ./source/gameplay/Map.cpp	    \
		    ./source/gameplay/Box.cpp	    \
		    ./source/gameplay/GameplayError.cpp\
		    ./source/gameplay/Character.cpp
GAMEPLAY_INCLUDE=   -I ./source/gameplay/

NETWORK_SRCS	=   ./source/network/Network.cpp    \
		    ./source/network/NetworkError.cpp
NETWORK_INCLUDE =   -I ./source/network/

MAIN_SRCS	=   ./source/main.cpp	   \
		    ./source/Graphics.cpp
MAIN_INCLUDE	=   -I ./source/

OBJS		=   $(LIB_SRCS:.cpp=.o)		\
		    $(GAMEPLAY_SRCS:.cpp=.o)	\
		    $(NETWORK_SRCS:.cpp=.o)	\
		    $(MAIN_SRCS:.cpp=.o)

CPPFLAGS	+=  $(LIB_INCLUDE)	\
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
