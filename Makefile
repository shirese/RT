# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/02 10:55:23 by chaueur           #+#    #+#              #
#    Updated: 2017/11/22 06:32:38 by chaueur          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= rt
TEST			= test
CC				= clang
FLAG			= -O3 -c -O1 -Wall -Werror -Wextra \
					-Wno-missing-field-initializers -pedantic -pthread
DEBUG			= -g -pthread -Wno-unused-parameter -Wno-unused-function \
					-Wno-unused-variable -Wno-uninitialized -Wno-missing-field-initializers
INCS			= -I include -I frameworks/SDL2.framework/Headers \
					-I ft_printf/inc/ 

SRC				=	environment.c main.c
SRC_CAMERA		=	camera.c camera_transform.c
SRC_COLOR		=	color.c color_op.c color_op_2.c color_utils.c
SRC_GEOS		=	cone.c cone2.c cylinder.c disk.c geo.c plane.c sphere.c
SRC_MATS		=	mat3.c mat3_rot.c mat4.c
SRC_PARSER		=	get_next_line.c cson_parser.c cson_parser_2.c \
					cson_parser_light.c cson_parser_geo.c
SRC_RENDER		=	ray.c raytracer.c render_thr.c
SRC_SDL			=	sdl.c sdl_event.c
SRC_SHADING		=	light.c lighting.c phong.c
SRC_TEX			=	checkerboard.c planar_mapping.c spherical_mapping.c \
					texture.c uv_texture.c
SRC_VECS		=	vec2.c \
					vec3.c vec3_adv_op.c vec3_basic_op.c vec3_basic_op_stack.c \
					vec3_utils.c\
					vec4.c vec4_utils.c
SRC_UTILS		=	math_utils.c math_utils_2.c transform.c utils.c

SRCS			= $(addprefix $(DIR_SRC)/, $(SRC))
SRCS_CAMERA		= $(addprefix $(DIR_SRC_CAMERA)/, $(SRC_CAMERA))
SRCS_COLOR		= $(addprefix $(DIR_SRC_COLOR)/, $(SRC_COLOR))
SRCS_GEOS		= $(addprefix $(DIR_SRC_GEOS)/, $(SRC_GEOS))
SRCS_MATS		= $(addprefix $(DIR_SRC_MATS)/, $(SRC_MATS))
SRCS_PARSER		= $(addprefix $(DIR_SRC_PARSER)/, $(SRC_PARSER))
SRCS_RENDER		= $(addprefix $(DIR_SRC_RENDER)/, $(SRC_RENDER))
SRCS_SDL		= $(addprefix $(DIR_SRC_SDL)/, $(SRC_SDL))
SRCS_SHADING	= $(addprefix $(DIR_SRC_SHADING)/, $(SRC_SHADING))
SRCS_TEX		= $(addprefix $(DIR_SRC_TEX)/, $(SRC_TEX))
SRCS_VECS		= $(addprefix $(DIR_SRC_VECS)/, $(SRC_VECS))
SRCS_UTILS		= $(addprefix $(DIR_SRC_UTILS)/, $(SRC_UTILS))

LIBFTPRINTF 	= ft_printf/libftprintf.a
LIB_SDL2		= -framework SDL2
LIB_PATH		= -F frameworks

DIR_SRC			= src
DIR_SRC_CAMERA	= src/camera
DIR_SRC_COLOR	= src/color
DIR_SRC_GEOS	= src/geometry
DIR_SRC_MATS	= src/matrice
DIR_SRC_PARSER	= src/parser
DIR_SRC_RENDER	= src/rendering
DIR_SRC_SDL		= src/sdl
DIR_SRC_SHADING	= src/shading
DIR_SRC_TEX		= src/texturing
DIR_SRC_VECS	= src/vector
DIR_SRC_UTILS	= src/utils

DIR_INC			= inc
DIR_OBJ			= obj

OBJ				= $(addprefix $(DIR_OBJ)/, $(SRC:.c=.o))
OBJ_CAMERA		= $(addprefix $(DIR_OBJ)/, $(SRC_CAMERA:.c=.o))
OBJ_COLOR		= $(addprefix $(DIR_OBJ)/, $(SRC_COLOR:.c=.o))
OBJ_GEOS		= $(addprefix $(DIR_OBJ)/, $(SRC_GEOS:.c=.o))
OBJ_MATS		= $(addprefix $(DIR_OBJ)/, $(SRC_MATS:.c=.o))
OBJ_PARSER		= $(addprefix $(DIR_OBJ)/, $(SRC_PARSER:.c=.o))
OBJ_RENDER		= $(addprefix $(DIR_OBJ)/, $(SRC_RENDER:.c=.o))
OBJ_SDL			= $(addprefix $(DIR_OBJ)/, $(SRC_SDL:.c=.o))
OBJ_SHADING		= $(addprefix $(DIR_OBJ)/, $(SRC_SHADING:.c=.o))
OBJ_TEX			= $(addprefix $(DIR_OBJ)/, $(SRC_TEX:.c=.o))
OBJ_VECS		= $(addprefix $(DIR_OBJ)/, $(SRC_VECS:.c=.o))
OBJ_UTILS		= $(addprefix $(DIR_OBJ)/, $(SRC_UTILS:.c=.o))

all : $(NAME)

debug :
	cd ft_printf && make;
	$(CC) $(FLAG) $(DEBUG) $(SRCS) $(SRCS_CAMERA) $(SRCS_COLOR) $(SRCS_GEOS) \
	$(SRCS_MATS) $(SRCS_PARSER) $(SRCS_RENDER) $(SRCS_SDL) $(SRCS_SHADING) \
	$(SRCS_TEX) $(SRCS_UTILS) $(SRCS_VECS) $(INCS)
	/bin/mkdir $(DIR_OBJ); \
	mv $(SRC:.c=.o) $(SRC_CAMERA:.c=.o) $(SRC_COLOR:.c=.o) $(SRC_GEOS:.c=.o) \
	$(SRC_MATS:.c=.o) $(SRC_PARSER:.c=.o)  $(SRC_RENDER:.c=.o) $(SRC_SDL:.c=.o) \
	$(SRC_SHADING:.c=.o) $(SRC_UTILS:.c=.o) $(SRC_TEX:.c=.o) $(SRC_VECS:.c=.o) \
	$(DIR_OBJ)/
	$(CC) $(LIB_PATH) $(LIB_SDL2) $(LIBFTPRINTF) -o $(NAME) $(OBJ) \
	$(OBJ_CAMERA) $(OBJ_COLOR) $(OBJ_GEOS) $(OBJ_MATS) $(OBJ_PARSER) \
	$(OBJ_RENDER) $(OBJ_SDL) $(OBJ_SHADING) $(OBJ_TEX) $(OBJ_UTILS) $(OBJ_VECS)
	@printf "\e[32m------------------------------------------------------\e[0m\n"
	@printf '\e[34m%-51s\e[0m\e[32m[✔]\e[0m\n' "created debug"
	@printf "\e[32m------------------------------------------------------\e[0m\n"

$(NAME) :
	cd ft_printf && make;
	$(CC) $(FLAG) $(SRCS) $(SRCS_CAMERA) $(SRCS_COLOR) $(SRCS_GEOS) \
	$(SRCS_MATS) $(SRCS_PARSER) $(SRCS_RENDER) $(SRCS_SDL) $(SRCS_SHADING) \
	$(SRCS_TEX) $(SRCS_UTILS) $(SRCS_VECS) $(INCS)
	@/bin/mkdir $(DIR_OBJ); \
	mv $(SRC:.c=.o) $(SRC_CAMERA:.c=.o) $(SRC_COLOR:.c=.o) $(SRC_GEOS:.c=.o) \
	$(SRC_MATS:.c=.o) $(SRC_PARSER:.c=.o)  $(SRC_RENDER:.c=.o) $(SRC_SDL:.c=.o) \
	$(SRC_SHADING:.c=.o) $(SRC_UTILS:.c=.o) $(SRC_TEX:.c=.o) $(SRC_VECS:.c=.o) \
	$(DIR_OBJ)/
	$(CC) $(LIB_PATH) $(LIB_SDL2) $(LIBFTPRINTF) -o $(NAME) $(OBJ) \
	$(OBJ_CAMERA) $(OBJ_COLOR) $(OBJ_GEOS) $(OBJ_MATS) $(OBJ_PARSER) \
	$(OBJ_RENDER) $(OBJ_SDL) $(OBJ_SHADING) $(OBJ_TEX) $(OBJ_UTILS) $(OBJ_VECS)
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
