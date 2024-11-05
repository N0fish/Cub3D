# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: algultse <algultse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/28 11:54:39 by roarslan          #+#    #+#              #
#    Updated: 2024/11/05 23:48:11 by algultse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
NAME_BONUS = $(NAME)

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCDIR) -I$(MLXDIR) -Imlx_linux
MLXFLAGS = -L$(MLXDIR) -lmlx -L/usr/lib -I$(MLXDIR) -lXext -lX11 -lm -g3 -lz -ffast-math -O3 -march=nativ

MLX = ./minilibx-linux/libmlx.a
MLXDIR = ./minilibx-linux/
SRCDIR = ./src/
INCDIR = ./include/
OBJDIR = ./obj/
MANDATORYDIR = ./src/
BONUSDIR = ./bonus/

SRC = get_next_line.c get_next_line_utils.c \
	utils.c utils2.c \
	check_map.c check_map2.c \
	assets_check.c \
	textures_check.c textures_color.c \
	check_2dmap.c check_2dmap2.c \
	check_around.c \
	free.c \
	ft_split.c \
	move.c \
	casting.c \
	draw.c minimap.c minimap2.c \
	xpm_to_image.c \
	movement.c \
	init.c

MANDATORY_SRC = $(MANDATORYDIR)main.c
BONUS_SRC = $(BONUSDIR)main_bonus.c

OBJS = $(SRC:%.c=$(OBJDIR)%.o)

MANDATORY_OBJS = $(OBJDIR)main.o
BONUS_OBJS = $(SRC:%.c=$(OBJDIR)%.o) $(BONUS_SRC:$(BONUSDIR)%.c=$(OBJDIR)%.o)

all: $(MLX) $(NAME)

$(NAME): $(OBJS) $(MANDATORY_OBJS)
	$(CC) $(OBJS) $(MANDATORY_OBJS) $(CFLAGS) $(MLX) $(MLXFLAGS) -o $(NAME)

bonus: $(MLX) $(BONUS_OBJS)
	$(CC) $(BONUS_OBJS) $(CFLAGS) $(MLX) $(MLXFLAGS) -o $(NAME_BONUS)

$(MLX):
	@make -C $(MLXDIR)
	@cp $(MLXDIR)libmlx.a $(MLXDIR)libmlx_Linux.a

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCDIR) -Imlx_linux -O3 -c $< -o $@

$(OBJDIR)main.o: $(MANDATORY_SRC)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCDIR) -Imlx_linux -O3 -c $< -o $@

$(OBJDIR)main_bonus.o: $(BONUS_SRC)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCDIR) -Imlx_linux -O3 -c $< -o $@

clean:
	rm -rf $(OBJDIR)
	make clean -C $(MLXDIR)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus valgrinds