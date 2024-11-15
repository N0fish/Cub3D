/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 22:41:33 by algultse          #+#    #+#             */
/*   Updated: 2024/11/05 23:39:47 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

// рисует пиксель на экране с цветом, который передаешь
void	draw_block_pixel(t_data *data, int pixel_x, int pixel_y, int color)
{
	char	*dst;

	if (!data)
		return ;
	dst = data->img->img_addr + (pixel_y * data->img->line_length \
			+ pixel_x * (data->img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

// цвет миникарты и рисует одну ячейку, либо черным нарисует, либо белым будет блок
void	draw_map_cell(t_data *data, t_minimap *minimap, int x, int y)
{
	int	i;
	int	j;
	int	pixel_x;
	int	pixel_y;
	int	color;

	if (!data || !minimap)
		return ;
	color = 0x000000;
	if (data->map->map2d[y][x] == '1')
		color = 0xFFFFFF;
	else if (data->map->map2d[y][x] == 'X')
		color = 0x0000FF;
	i = 0;
	while (i < minimap->map_scale)
	{
		j = 0;
		while (j < minimap->map_scale)
		{
			pixel_x = minimap->offset_x + x * minimap->map_scale + i;
			pixel_y = minimap->offset_y + y * minimap->map_scale + j;
			draw_block_pixel(data, pixel_x, pixel_y, color);
			j++;
		}
		i++;
	}
}

// рисует все блоки карты, стены и пространство
void	draw_map_blocks(t_data *data, t_minimap *minimap)
{
	int	x;
	int	y;

	if (!data || !minimap)
		return ;
	y = 0;
	while (y < data->map->size)
	{
		x = 0;
		while (x < data->map->max_len)
		{
			if (data->map->map2d[y][x] == '1' || data->map->map2d[y][x] == '0' \
				|| data->map->map2d[y][x] == 'X')
				draw_map_cell(data, minimap, x, y);
			x++;
		}
		y++;
	}
}

