# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/02 10:55:23 by chaueur           #+#    #+#              #
#    Updated: 2017/11/04 15:44:33 by chaueur          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= rt
TEST			= test
CC				= clang
FLAG			= -O3 -c -O1 -Wall -Werror -Wextra -pedantic
DEBUG			= -g -Wno-unused-parameter -Wno-unused-function \
					-Wno-unused-variable -Wno-uninitialized
INCS			= -I inc -I frameworks/SDL2.framework/Headers -I ft_printf/inc/
SRC				=	camera.c camera_transform.c color.c color_utils.c \
					environment.c main.c math_utils.c light.c lighting.c \
					phong.c ray.c raytracer.c sdl.c sdl_event.c transform.c \
					utils.c
SRC_PARSER		=	get_next_line.c cson_parser.c cson_parser_2.c cson_parser_light.c\
					cson_parser_geo.c
SRC_GEOS		=	cone.c cone2.c cylinder.c disk.c geo.c plane.c sphere.c
SRC_MATS		=	mat3.c mat3_rot.c mat4.c
SRC_VECS		=	vec3.c vec3_adv_op.c vec3_basic_op.c vec3_basic_op_stack.c\
					vec3_utils.c\
					vec4.c vec4_utils.c

SRCS			= $(addprefix $(DIR_SRC)/, $(SRC))
SRCS_GEOS		= $(addprefix $(DIR_SRC_GEOS)/, $(SRC_GEOS))
SRCS_PARSER		= $(addprefix $(DIR_SRC_PARSER)/, $(SRC_PARSER))
SRCs_mat3S		= $(addprefix $(DIR_SRC_MATS)/, $(SRC_MATS))
SRCS_VECS		= $(addprefix $(DIR_SRC_VECS)/, $(SRC_VECS))

LIBFTPRINTF 	= ft_printf/libftprintf.a
LIB_SDL2		= -framework SDL2
LIB_PATH		= -F frameworks

DIR_SRC			= src
DIR_SRC_GEOS	= src/geometry
DIR_SRC_PARSER	= src/parser
DIR_SRC_MATS	= src/matrice
DIR_SRC_VECS	= src/vector
DIR_INC			= inc
DIR_OBJ			= obj
OBJ				= $(addprefix $(DIR_OBJ)/, $(SRC:.c=.o))
OBJ_GEOS		= $(addprefix $(DIR_OBJ)/, $(SRC_GEOS:.c=.o))
OBJ_PARSER		= $(addprefix $(DIR_OBJ)/, $(SRC_PARSER:.c=.o))
OBJ_MATS		= $(addprefix $(DIR_OBJ)/, $(SRC_MATS:.c=.o))
OBJ_VECS		= $(addprefix $(DIR_OBJ)/, $(SRC_VECS:.c=.o))

all : $(NAME)

debug :
	$(CC) $(FLAG) $(DEBUG) $(SRCS) $(SRCS_GEOS) $(SRCS_PARSER) $(SRCs_mat3S) $(SRCS_VECS) $(INCS)
	/bin/mkdir $(DIR_OBJ); \
	mv $(SRC:.c=.o) $(SRC_GEOS:.c=.o) $(SRC_PARSER:.c=.o) $(SRC_MATS:.c=.o) $(SRC_VECS:.c=.o) $(DIR_OBJ)/
	$(CC) $(LIB_PATH) $(LIB_SDL2) $(LIBFTPRINTF) -o $(NAME) $(OBJ) $(OBJ_GEOS) $(OBJ_PARSER) $(OBJ_MATS) $(OBJ_VECS)
	@printf "\e[32m------------------------------------------------------\e[0m\n"
	@printf '\e[34m%-51s\e[0m\e[32m[✔]\e[0m\n' "created debug"
	@printf "\e[32m------------------------------------------------------\e[0m\n"

$(NAME) :
	cd ft_printf && make;
	$(CC) $(FLAG) $(SRCS) $(SRCS_GEOS) $(SRCS_PARSER) $(SRCs_mat3S) $(SRCS_VECS) $(INCS)
	@/bin/mkdir $(DIR_OBJ); \
	mv $(SRC:.c=.o) $(SRC_GEOS:.c=.o) $(SRC_PARSER:.c=.o) $(SRC_MATS:.c=.o) $(SRC_VECS:.c=.o) $(DIR_OBJ)/
	$(CC) $(LIB_PATH) $(LIB_SDL2) $(LIBFTPRINTF) -o $(NAME) $(OBJ) $(OBJ_GEOS) $(OBJ_PARSER) $(OBJ_MATS) $(OBJ_VECS)
	@printf "\e[32m------------------------------------------------------\e[0m\n"
	@printf '\e[34m%-51s\e[0m\e[32m[✔]\e[0m\n' "created $(NAME)"
	@printf "\e[32m------------------------------------------------------\e[0m\n"


$(addprefix $(DIR_OBJ)/, %.o) : %.c
	@printf "compiling \e[33m%-41s\e[0m" "$@"
	@$(CC) $(FLAG) $@ $<
	@printf "\e[32m[✔]\e[0m\n"

clean :
	cd ft_printf && make clean;
	@if [ -e '$(DIR_OBJ)' ]; then \
		/bin/rm	-rf $(DIR_OBJ); \
		printf "\e[32m[✔]\e[0m project %s cleaned.\n" $(NAME); \
		fi

fclean : clean
	cd ft_printf && make fclean;
	@if [ -e '$(NAME)' ]; then \
		/bin/rm -f $(NAME); \
		printf "\e[32m[✔]\e[0m project %s fcleaned.\n" $(NAME); \
		fi

re : fclean all

.PHONY:	clean fclean re
