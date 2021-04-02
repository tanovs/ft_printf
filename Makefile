# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atable <atable@student.school-21.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/04 20:08:04 by atable            #+#    #+#              #
#    Updated: 2020/07/14 19:49:45 by atable           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

LIBFT = libft.a

LIBDIR = libft

FLAGS = -Wall -Wextra -Werror

HDR = libftprintf.h

SRC = ft_printf.c \
		ft_write.c \
		ft_convert.c \
		ft_flags.c \
		ft_parse_string.c \
		ft_check.c \
		ft_noname_func.c

OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBDIR)
	@cp $(LIBDIR)/$(LIBFT) .
	@mv $(LIBFT) $(NAME)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo Merged: $(NAME) with $(LIBFT)

%.o: %.c $(HDR)
	@gcc $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@make -C $(LIBDIR) clean 

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBDIR) fclean

re: fclean all
