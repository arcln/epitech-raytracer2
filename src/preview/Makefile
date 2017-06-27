##
## Makefile for raytracer2 in /home/onehandedpenguin/Dev/CGP_2016/Preview/
##
## Made by Paul Laffitte
## Login   <paul.laffitte@epitech.eu>
##
## Started on  Thu May 25 16:25:33 2017 Paul Laffitte
## Last update Tue Jun  6 13:54:31 2017 Arthur Chaloin
##

NAME			=	raytracer2_preview

BIN_PATH		=	../../bin/

CC			=	g++

RM			=	rm -f

CXXFLAGS	=	-std=c++14 -W -Wall -Wextra
CXXFLAGS	+=	-I./
CXXFLAGS	+=	-I../lib/
CXXFLAGS	+=	-I../pixel/
CXXFLAGS	+=	-I../scene/
CXXFLAGS	+=	-I../scene/mesh/
CXXFLAGS	+=	-I../scene/ray/
CXXFLAGS	+=	-I../network/client/
CXXFLAGS	+=	-I../parser/
CXXFLAGS	+=	`pkg-config --cflags glfw3 glew`

LDFLAGS		=	-lsfml-graphics -lsfml-window -lsfml-system
LDFLAGS		+=	-lpthread
LDFLAGS		+=	-lm
LDFLAGS		+=	-lassimp
LDFLAGS		+=	-framework OpenGL
LDFLAGS		+=	`pkg-config --static --libs glfw3 glew`

SRC			=	main.cpp				\
				core/preview.cpp			\
				core/video.cpp				\
				../lib/eq.cpp				\
				../lib/vector.cpp			\
				../lib/matrix.cpp			\
				../lib/perlin.cpp			\
				../pixel/pixel.cpp			\
				../pixel/texture.cpp			\
				../scene/scene.cpp			\
				../scene/camera.cpp			\
				../scene/mesh/mesh.cpp			\
				../scene/mesh/objects/sphere.cpp	\
				../scene/mesh/objects/plane.cpp		\
				../scene/mesh/objects/cylinder.cpp	\
				../scene/mesh/objects/triangle.cpp	\
				../scene/ray/ray.cpp			\
				../network/client/client.cpp		\
				../parser/parser.cpp



OBJ			=	$(SRC:.cpp=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)
		mv $(NAME) $(BIN_PATH)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(BIN_PATH)$(NAME)

re:		fclean all

debug:	CXXFLAGS += -g
debug:	re

fast:	CXXFLAGS += -Ofast
fast:	re

.PHONY:		all clean fclean re
