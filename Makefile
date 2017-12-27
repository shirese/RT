# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/02 10:55:23 by chaueur           #+#    #+#              #
#    Updated: 2017/12/27 14:18:56 by chaueur          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= rt
TEST			= test
CC				= clang

FLAG			= -O3 -O1 -Wall -Werror -Wextra -pedantic -pthread -Wno-missing-field-initializers
INCS			= -I include -I frameworks/SDL2.framework/Headers -I ft_printf/inc/

DIR_SRC			= src/
DIR_SRC_CAMERA	= camera/
DIR_SRC_COLOR	= color/
DIR_SRC_GEOS	= geometry/
DIR_SRC_MATS	= matrice/
DIR_SRC_PARSER	= parser/
DIR_SRC_RENDER	= rendering/
DIR_SRC_SDL		= sdl/
DIR_SRC_SHADING	= shading/
DIR_SRC_TEX		= texturing/
DIR_SRC_VECS	= vector/
DIR_SRC_UTILS	= utils/

DIR_INC			= inc/
DIR_OBJ			= obj/

SRC_MAIN		=	environment.c main.c
SRC_CAMERA		=	camera.c camera_transform.c
SRC_COLOR		=	color.c color_op.c color_op_2.c color_utils.c filters.c \
					filters_2.c
SRC_GEOS		=	cone.c cone2.c cone3.c cut.c cut2.c cut3.c cylinder1.c cylinder2.c disk.c geo1.c geo2.c negativity1.c negativity2.c \
					paraboloid.c plane.c sphere.c
SRC_MATS		=	mat3.c mat3_rot.c mat4.c mat4_utils.c
SRC_PARSER		=	get_next_line.c cson_parser.c cson_parser_2.c \
					cson_parser_light.c cson_parser_geo.c cson_parser_geo2.c
SRC_RENDER		=	ray.c ray_ref.c raytracer.c raytracer_ref.c render.c render_thr.c
SRC_SDL			=	sdl.c sdl_bar.c sdl_drag.c sdl_event.c
SRC_SHADING		=	fresnel.c light.c lighting.c phong.c toon.c
SRC_TEX			=	checkerboard.c perlin.c planar_mapping.c spherical_mapping.c texture.c uv_texture.c
SRC_UTILS		=	geo_utils.c math_utils.c math_utils_2.c print_utils.c transform.c utils.c
SRC_VECS		=	vec2.c\
					vec3.c vec3_adv_op.c vec3_basic_op.c vec3_basic_op_stack.c\
					vec3_utils.c\
					vec4.c vec4_utils.c

SRCS			= $(SRC_MAIN)
SRCS			+= $(SRC_CAMERA)
SRCS			+= $(SRC_COLOR)
SRCS			+= $(SRC_GEOS)
SRCS			+= $(SRC_MATS)
SRCS			+= $(SRC_PARSER)
SRCS			+= $(SRC_RENDER)
SRCS			+= $(SRC_SDL)
SRCS			+= $(SRC_SHADING)
SRCS			+= $(SRC_TEX)
SRCS			+= $(SRC_UTILS)
SRCS			+= $(SRC_VECS)

OBJS			= $(SRCS:.c=.o)

SRC				= $(SRC_MAIN)
SRC				+= $(addprefix $(DIR_SRC_CAMERA),$(SRC_CAMERA))
SRC				+= $(addprefix $(DIR_SRC_COLOR),$(SRC_COLOR))
SRC				+= $(addprefix $(DIR_SRC_GEOS),$(SRC_GEOS))
SRC				+= $(addprefix $(DIR_SRC_MATS),$(SRC_MATS))
SRC				+= $(addprefix $(DIR_SRC_PARSER),$(SRC_PARSER))
SRC				+= $(addprefix $(DIR_SRC_RENDER),$(SRC_RENDER))
SRC				+= $(addprefix $(DIR_SRC_SDL),$(SRC_SDL))
SRC				+= $(addprefix $(DIR_SRC_SHADING),$(SRC_SHADING))
SRC				+= $(addprefix $(DIR_SRC_TEX),$(SRC_TEX))
SRC				+= $(addprefix $(DIR_SRC_UTILS),$(SRC_UTILS))
SRC				+= $(addprefix $(DIR_SRC_VECS),$(SRC_VECS))
SRC				:= $(addprefix $(DIR_SRC),$(SRCS))

OBJ				= $(addprefix $(DIR_OBJ),$(OBJS))

VPATH			= $(DIR_SRC)
VPATH			+= $(addprefix $(DIR_SRC),$(DIR_SRC_CAMERA))
VPATH			+= $(addprefix $(DIR_SRC),$(DIR_SRC_COLOR))
VPATH			+= $(addprefix $(DIR_SRC),$(DIR_SRC_GEOS))
VPATH			+= $(addprefix $(DIR_SRC),$(DIR_SRC_MATS))
VPATH			+= $(addprefix $(DIR_SRC),$(DIR_SRC_PARSER))
VPATH			+= $(addprefix $(DIR_SRC),$(DIR_SRC_RENDER))
VPATH			+= $(addprefix $(DIR_SRC),$(DIR_SRC_SDL))
VPATH			+= $(addprefix $(DIR_SRC),$(DIR_SRC_SHADING))
VPATH			+= $(addprefix $(DIR_SRC),$(DIR_SRC_TEX))
VPATH			+= $(addprefix $(DIR_SRC),$(DIR_SRC_UTILS))
VPATH			+= $(addprefix $(DIR_SRC),$(DIR_SRC_VECS))

LIBFTPRINTF		= ft_printf/libftprintf.a
LIB_SDL2		= -framework SDL2
LIB_PATH		= -F frameworks

all: $(NAME)

debug: FLAG += -g -Wno-unused-parameter -Wno-unused-function -Wno-unused-variable -Wno-uninitialized
debug: $(NAME)

$(NAME): $(LIBFTPRINTF) $(OBJ)
	$(CC) $(LIB_PATH) $(LIB_SDL2) $(LIBFTPRINTF) $^ -o $@

$(LIBFTPRINTF):
	@make -C ft_printf/

$(DIR_OBJ)%.o: %.c
	@mkdir $(DIR_OBJ) 2> /dev/null || true
	$(CC) $(FLAG) $(INCS) -o $@ -c $<

clean:
	@make -C ft_printf/ fclean
	rm -fv $(OBJ)
	@rmdir $(DIR_OBJ) 2> /dev/null || true

fclean: clean
	@make -C ft_printf/ clean
	rm -rf $(NAME)

re: fclean all

.PHONE: all, clean, fclean, re
