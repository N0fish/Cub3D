/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 22:47:01 by algultse          #+#    #+#             */
/*   Updated: 2024/11/05 22:49:32 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

# include "includes.h"

# define MOUSE_SENSITIVITY 0.002
# define WIDTH 1024
# define HEIGHT 768
# define NUM_SPRITES 1

typedef struct s_data	t_data;
typedef struct s_map	t_map;

typedef struct s_minimap
{
	int	map_size;
	int	map_scale;
	int	offset_x;
	int	offset_y;
	int	player_x;
	int	player_y;
}	t_minimap;

typedef struct s_sprite
{
	double	x;
	double	y;
	int		current_frame;
	int		num_frames;
	void	**textures;
}	t_sprite;

typedef struct s_sprite_transform
{
	double	spriteX;
	double	spriteY;
	double	transformX;
	double	transformY;
	int		spriteScreenX;
	int		spriteHeight;
	int		spriteWidth;
	int		drawStartX;
	int		drawEndX;
	int		drawStartY;
	int		drawEndY;
}	t_sprite_transform;

typedef struct s_sprite_texture_data
{
	char	*sprite_data;
	int		bpp;
	int		size_line;
	int		endian;
	int		texWidth;
	int		texHeight;
}	t_sprite_texture_data;

typedef struct s_texture_coordinates
{
	int	texX;
	int	texY;
}	t_texture_coordinates;

//minimap
void	draw_minimap(t_data *data);
void	draw_map_blocks(t_data *data, t_minimap *minimap);
void	draw_block_pixel(t_data *data, int pixel_x, int pixel_y, int color);

//sprites
void	init_sprites(t_data *data);
void	draw_sprites(t_data *data);
void	init_sprites(t_data *data);
void	calculate_sprite_transform(t_data *data, t_sprite *sprite, \
									t_sprite_transform *tdata);


//utils_sprite
void	handle_sprite(char *line, int i, t_map *map);
void	free_sprites(t_data *data);
char	*ft_strjoin_b(char const *s1, char const *s2);
char	*ft_itoa(int n);

#endif
