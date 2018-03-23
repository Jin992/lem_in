# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: earteshc <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/05 12:22:40 by earteshc          #+#    #+#              #
#    Updated: 2018/03/10 14:16:52 by jdoeeshc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
CC = @gcc
CFLAGS = -Wall -Wextra -Werror -Ilib/includes
VOICE = d

LEM_IN = main.c check_ants.c check_links.c check_path.c check_room.c\
check_room_helpers.c free_funcs.c make_route.c make_route_helpers.c\
move_ants.c realloc_funcs.c validation.c validation_helpers.c

OBJ = $(LEM_IN:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Compiling libft wait..."
	@make -C ./lib/
	@echo "Compiling lem-in wait..."
	@gcc -L ./lib/ -lft $(OBJ) -o $(NAME)
	@echo "Done."

clean:
	@make -C ./lib/ clean
	@/bin/rm -f $(OBJ)

fclean: clean
	@make -C ./lib/ fclean
	@/bin/rm -f $(NAME)

re: fclean all
