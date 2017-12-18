# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/05 10:52:33 by chaueur           #+#    #+#              #
#    Updated: 2017/10/17 16:45:12 by chaueur          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = gcc

SRC_DIR = ./src

INC_DIR = ./inc

SRC = 	ft_printf.c get_options.c conver_num.c conver_char.c conver_wchar.c\
		conver_arg.c\
		ft_atoi.c ft_atof.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
		ft_isblank.c ft_isdigit.c ft_isprint.c ft_isspace.c ft_itoa.c \
		ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c\
		ft_memdel.c ft_memmove.c ft_memset.c ft_putchar.c ft_putchar_fd.c\
		ft_putnbr.c ft_putstr.c ft_putstr_fd.c ft_strcat.c ft_strchr.c\
		ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c\
		ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c ft_strlcat.c\
		ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncmp.c \
		ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c \
		ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtrim.c ft_tolower.c \
		ft_toupper.c ft_lstnew.c ft_lstdelone.c ft_putendl.c ft_putendl_fd.c \
		ft_putnbr_fd.c ft_lstadd.c ft_realloc.c ft_strrev.c ft_strnrev.c ft_strtoupper.c \
		ft_itoa_base.c ft_itoa_unsig_base.c ft_ftoa.c ft_strfjoin.c\

SRC_0 = $(SRC:%.c=%.o)

SRCS = $(patsubst %,$(SRC_DIR)/%,$(SRC))

FLAG = -Wall -Wextra -Werror

INC = -I $(INC_DIR)

all: $(NAME)

$(NAME):
	$(CC) $(FLAG) $(INC) -c $(SRCS)
	ar rc $(NAME) $(SRC_0)
	ranlib $(NAME)

test:
	gcc test.c libftprintf.a
	./a.out

clean:
	@rm -f $(SRC_0)

fclean:	clean
	@rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re
