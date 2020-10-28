# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/25 13:25:38 by snorthmo          #+#    #+#              #
#    Updated: 2020/10/28 11:40:45 by snorthmo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC = cast_rays.c\
		cast_sprites.c\
		check.c\
		free_errors.c\
		game_init.c\
		init.c\
		key_press.c\
		map2d.c\
		parser.c\
		running_around.c\
		save_bmp.c\
		sprites_and_player.c\
		textures.c\
		validity.c

OBJ = $(SRC:.c=.o)

CC = gcc

RM = rm -rf

CFLAG = -g -Wall -Wextra -Werror -Imlx

LIB = -Lmlx -lmlx -framework OpenGL -framework AppKit -lm -Llibft -lft

MLX_LIB = libmlx.dylib

LIBFT = libft/libft.a

HEADER = -I./includes

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) $(MLX_LIB) $(LIBFT)
		$(CC) $(CFLAG) -o $(NAME) $(OBJ) $(HEADER) $(LIB)
		@cp mlx/$(MLX_LIB) .

%.o: %.c
		$(CC) $(HEADER) $(CFLAG) -c $< -o $@ -g

$(LIBFT): $(MLX_LIB)
		@$(MAKE) -C libft

$(MLX_LIB):
		@$(MAKE) -C mlx

clean:
		$(MAKE) clean -C ./libft
		$(RM) $(OBJ)

fclean: clean
		$(MAKE) fclean -C ./libft
		$(MAKE) clean -C ./mlx
		$(RM) $(NAME) $(MLX_LIB)

re: fclean $(NAME)

.PHONY: all clean fclean re
