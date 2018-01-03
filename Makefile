# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgurova <dariagurova91@gmail.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/19 17:46:50 by dgurova           #+#    #+#              #
#    Updated: 2017/12/19 17:46:54 by dgurova          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

FLAGS = -Wall -Wextra -Werror
ATTACH = -L./minilibx_macos/ -lmlx -framework OpenGL -framework AppKit -L./libft -lft

SRC = main.c apply_proj.c draw_lines.c key_events.c \
	  parse_args.c validate_args.c 
OBJ = $(subst .c,.o,$(SRC))

all: $(NAME)

$(NAME):
	make -C libft/
	gcc $(FLAGS) -I libft/ -c $(SRC)
	gcc $(FLAGS) -o $(NAME) $(OBJ) $(ATTACH)

run42:
	./fdf tests/42.fdf

clean:
	rm -f $(OBJ)
	make -C libft/ clean

fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean

re: fclean all

