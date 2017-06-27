##
## Makefile for rt in /home/arthur/B2/MUL/raytracer2/
##
## Made by John Doe
## Login   <login_x@epitech.eu>
##
## Started on  Fri Mar 24 10:06:29 2017 John Doe
## Last update Fri Apr 14 18:51:48 2017 Arthur Chaloin
##

NAME		=	server

CC			=	g++

RM			=	rm -f

CXXFLAGS	=	-std=c++14 -W -Wall -Wextra

LDFLAGS		=	-lpthread

SRC			=	main.cpp	\
				server.cpp

OBJ			=	$(SRC:.cpp=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

debug:	CXXFLAGS += -g
debug:	re

.PHONY:		all clean fclean re
