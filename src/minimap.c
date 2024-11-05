/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:56:20 by algultse          #+#    #+#             */
/*   Updated: 2024/11/05 23:38:23 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

// нах-ся ли персонаж в пределах границ
int	is_within_minimap_bounds(int px, int py, t_minimap *minimap)
{
	return ( \
		px >= minimap->offset_x \
		&& px < minimap->offset_x + minimap->map_size \
		&& py >= minimap->offset_y \
		&& py < minimap->offset_y + minimap->map_size \
		);
}

// рисовка игрока (красный кружок)
void	draw_player_icon(t_data *data, t_minimap *minimap)
{
	int	i;
	int	j;
	int	px;
	int	py;
	int	player_radius;

	player_radius = 3;
	i = -player_radius;
	while (i <= player_radius)
	{
		j = -player_radius;
		while (j <= player_radius)
		{
			if (i * i + j * j <= player_radius * player_radius)
			{
				px = minimap->player_x + i;
				py = minimap->player_y + j;
				if (is_within_minimap_bounds(px, py, minimap))
					draw_block_pixel(data, px, py, 0xFF0000);
			}
			j++;
		}
		i++;
	}
}

// функция чтобы нарисовать миникарту
void	draw_minimap(t_data *data)
{
	t_minimap	minimap;

	minimap.map_size = 150;
	minimap.offset_x = 20;
	minimap.offset_y = 20;
	if (data->map->size > data->map->max_len)
		minimap.map_scale = minimap.map_size / data->map->size;
	else
		minimap.map_scale = minimap.map_size / data->map->max_len;
	minimap.player_x = minimap.offset_x \
						+ (int)(data->game->posx * minimap.map_scale);
	minimap.player_y = minimap.offset_y \
						+ (int)(data->game->posy * minimap.map_scale);
	draw_map_blocks(data, &minimap);
	draw_player_icon(data, &minimap);
}
