# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: algultse <algultse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/28 11:54:39 by roarslan          #+#    #+#              #
#    Updated: 2024/11/15 18:48:03 by algultse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
NAME_BONUS = $(NAME)
FLAG_FILE = bonus_built

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
	check_map.c check_map2.c assets_check.c \
	textures_check.c textures_color.c \
	check_2dmap.c check_2dmap2.c check_around.c \
	free.c ft_split.c \
	move.c casting.c draw.c \
	xpm_to_image.c movement.c \
	init.c

SRCS_BONUS = $(BONUSDIR)get_next_line.c $(BONUSDIR)get_next_line_utils.c \
	$(BONUSDIR)utils.c $(BONUSDIR)utils2.c \
	$(BONUSDIR)check_map.c $(BONUSDIR)check_map2.c $(BONUSDIR)assets_check.c \
	$(BONUSDIR)textures_check.c $(BONUSDIR)textures_color.c \
	$(BONUSDIR)check_2dmap.c $(BONUSDIR)check_2dmap2.c $(BONUSDIR)check_around.c \
	$(BONUSDIR)free.c $(BONUSDIR)ft_split.c \
	$(BONUSDIR)move.c $(BONUSDIR)casting.c \
	$(BONUSDIR)draw.c $(BONUSDIR)minimap.c $(BONUSDIR)minimap2.c \
	$(BONUSDIR)xpm_to_image.c $(BONUSDIR)movement.c \
	$(BONUSDIR)init.c $(BONUSDIR)allocate.c $(BONUSDIR)init_sprites.c \
	$(BONUSDIR)ft_itoa.c $(BONUSDIR)utils_sprite.c \
	$(BONUSDIR)draw_sprite.c $(BONUSDIR)draw_sprite_calculate.c \
	$(BONUSDIR)mouse_move.c

MANDATORY_SRC = $(MANDATORYDIR)main.c
BONUS_SRC = $(BONUSDIR)main_bonus.c

OBJS = $(SRC:%.c=$(OBJDIR)%.o)

MANDATORY_OBJS = $(OBJDIR)main.o

OBJDIR_BONUS = ./obj_bonus/
BONUS_OBJS = $(SRCS_BONUS:$(BONUSDIR)%.c=$(OBJDIR_BONUS)%.o) $(BONUS_SRC:$(BONUSDIR)%.c=$(OBJDIR_BONUS)%.o)

all: $(MLX) $(NAME)

$(NAME): $(OBJS) $(MANDATORY_OBJS)
	$(CC) $(OBJS) $(MANDATORY_OBJS) $(CFLAGS) $(MLX) $(MLXFLAGS) -o $(NAME)

bonus: $(MLX) $(NAME_BONUS) $(FLAG_FILE)

$(FLAG_FILE): $(MLX) $(BONUS_OBJS)
	$(CC) $(BONUS_OBJS) $(CFLAGS) $(MLX) $(MLXFLAGS) -o $(NAME_BONUS)
	@touch $(FLAG_FILE)

$(MLX):
	@make -C $(MLXDIR)
	@cp $(MLXDIR)libmlx.a $(MLXDIR)libmlx_Linux.a

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCDIR) -Imlx_linux -O3 -c $< -o $@

$(OBJDIR)main.o: $(MANDATORY_SRC)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCDIR) -Imlx_linux -O3 -c $< -o $@

$(OBJDIR_BONUS)%.o: $(BONUSDIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCDIR) -Imlx_linux -O3 -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(OBJDIR_BONUS)
	make clean -C $(MLXDIR)

fclean: clean
	rm -f $(NAME) $(FLAG_FILE)

re: fclean all

.PHONY: all clean fclean re bonus valgrinds