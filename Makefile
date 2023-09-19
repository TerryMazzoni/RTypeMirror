##
## EPITECH PROJECT, 2023
## RTypeMirror
## File description:
## Makefile
##

SRC_SERVER	=	src/server/main.cpp		\
				src/server/Server.cpp	\
				src/server/Args.cpp		\

SRC_CLIENT	=	src/client/main.cpp		\
				src/client/Client.cpp	\
				src/client/Args.cpp		\

OBJ_SERVER	=	$(SRC_SERVER:.cpp=.o)

OBJ_CLIENT	=	$(SRC_CLIENT:.cpp=.o)

NAME_SERVER	=	r-type_server

NAME_CLIENT	=	r-type_client

CXXFLAGS	=	-W -Wall -Wextra -std=c++17 -I./src/communication

all: $(OBJ_CLIENT) $(OBJ_SERVER)
	g++ -o $(NAME_SERVER) $(OBJ_SERVER) -lboost_serialization -lpthread
	g++ -o $(NAME_CLIENT) $(OBJ_CLIENT) -lboost_serialization -lpthread

clean:
	rm -f $(OBJ_SERVER)
	rm -f $(OBJ_CLIENT)

fclean: clean
	rm -f $(NAME_SERVER)
	rm -f $(NAME_CLIENT)

re: fclean all

debug: CXXFLAGS += -g
debug: re
				