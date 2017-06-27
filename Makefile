##
## Makefile for rt in /home/arthur/B2/MUL/raytracer2/
##
## Made by John Doe
## Login   <login_x@epitech.eu>
##
## Started on  Fri Mar 24 10:06:29 2017 John Doe
## Last update Sun May 28 15:15:22 2017 Arthur Chaloin
##

NAME			=	raytracer2

BIN_PATH		=	./bin/

CC			=	g++

RM			=	rm -f

CXXFLAGS	=	-std=c++14 -W -Wall -Wextra
CXXFLAGS	+=	-I./src/lib/
CXXFLAGS	+=	-I./src/pixel/
CXXFLAGS	+=	-I./src/scene/
CXXFLAGS	+=	-I./src/scene/mesh/
CXXFLAGS	+=	-I./src/scene/ray/
CXXFLAGS	+=	-I./src/network/client/
CXXFLAGS	+=	-I./src/parser/

LDFLAGS		=	-lsfml-graphics -lsfml-window -lsfml-system -lpthread

SRC			=	src/raytracer.cpp					\
				src/lib/eq.cpp						\
				src/lib/vector.cpp					\
				src/lib/perlin.cpp					\
				src/lib/matrix.cpp					\
				src/pixel/pixel.cpp					\
				src/pixel/texture.cpp					\
				src/scene/scene.cpp					\
				src/scene/camera.cpp				\
				src/scene/mesh/mesh.cpp				\
				src/scene/mesh/objects/sphere.cpp	\
				src/scene/mesh/objects/plane.cpp	\
				src/scene/mesh/objects/cylinder.cpp	\
				src/scene/mesh/objects/triangle.cpp	\
				src/scene/ray/ray.cpp				\
				src/network/client/client.cpp		\
				src/parser/parser.cpp

OBJ			=	$(SRC:.cpp=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)
		cp $(NAME) $(BIN_PATH)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(BIN_PATH)$(NAME)

re:		fclean all

debug:	CXXFLAGS += -g
debug:	re

fast:	CXXFLAGS += -Ofast
fast:	re

.PHONY:		all clean fclean re debug fast
