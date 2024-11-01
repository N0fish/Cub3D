# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roarslan <roarslan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/28 11:54:39 by roarslan          #+#    #+#              #
#    Updated: 2024/10/30 16:21:49 by roarslan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC = src/main.c \
	src/get_next_line.c \
	src/get_next_line_utils.c \
	src/utils.c \
	src/utils2.c \
	src/check_map.c \
	src/check_map2.c \
	src/assets_check.c \
	src/textures_check.c \
	src/textures_color.c \
	src/check_2dmap.c \
	src/check_2dmap2.c \
	src/check_around.c \
	src/free.c \
	src/ft_split.c \
	src/move.c \
	src/casting.c \
	src/draw.c \
	src/xpm_to_image.c \
	src/movement.c \
	src/init.c

HEADER = includes.h

MLX = minilibx-linux/libmlx.a \
      	minilibx-linux/libmlx_Linux.a

OBJ_DIR = obj

OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	make -C minilibx-linux
	$(CC) $(OBJ) $(CFLAGS) $(MLX) -Lmlx-linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm  -g3 -lz -ffast-math -O3 -march=native -Ofast -o $(NAME)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -Iusr/include -Imlx_linux -O3 -c $< -o $@

clean:
	make clean -C ./minilibx-linux
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all valgrind
