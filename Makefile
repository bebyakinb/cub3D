# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/04 18:31:56 by enoelia           #+#    #+#              #
#    Updated: 2021/06/30 17:52:03 by enoelia          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
F = source
C = main.c \
		hooks.c \
		drawer.c \
		sprites.c \
		map_drawer.c \
		map_checker.c \
		parser_colors.c \
		parser_textures.c \
		correction_checker.c \
		parser_screen_scale.c \
		bmp.c \
		init1.c \
		init2.c \
		parser.c \
		raycasting.c \
		error_exit.c

C_SRC =  $(addprefix $F/, $C)

O_SRC = $(C_SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

LIB_PATH = libft

LIB = $(LIB_PATH)/libft.a

MLX_PATH = minilibx-linux

MLX = libmlx.a

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIB) $(MLX) $F/cub3d.h $(O_SRC)
	gcc -o $(NAME) $(FLAGS) -L $(MLX_PATH) $(O_SRC) $(LIB_PATH)/libft.a -lmlx -lm -lbsd -lX11 -lXext
$(LIB):
	make -C $(LIB_PATH) bonus 

$(MLX):
	make -C $(MLX_PATH)
	cp $(MLX_PATH)/$(MLX) ./

%.o: %.c $F/cub3d.h
	gcc $(FLAGS) -I$F -I$(MLX_PATH) -I$(LIB_PATH) -c $< -o $@

clean: 
	/bin/rm -f $(O_SRC)
	make -C $(LIB_PATH) clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C $(LIB_PATH) fclean
	make -C $(MLX_PATH) clean
	/bin/rm -f $(MLX)

re: fclean all