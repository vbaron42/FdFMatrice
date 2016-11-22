# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbaron <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/26 00:59:46 by vbaron            #+#    #+#              #
#    Updated: 2016/11/22 20:25:20 by vbaron           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fdf
FLAGS	=	-lmlx -framework OpenGL -framework AppKit
CC		=	gcc
SRC		=	main.c segment_put.c img.c event.c matrice.c color.c
OBJ		=	$(SRC:.c=.o)

all:		$(NAME)

$(NAME):
	cd libft/ && $(MAKE)
	$(CC) $(FLAGS) $(SRC) -L ./libft -lft -o $(NAME)
	cd libft/ && $(MAKE) fclean

%.o: %.c
	$(cc) $(FLAGS) -c $^ -o $@

norminette:
	norminette $(SRC)
	norminette fdf.h

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
