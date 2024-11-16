/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 20:31:23 by algultse          #+#    #+#             */
/*   Updated: 2024/11/13 21:45:50 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

static void	get_sprite_texture_data(t_sprite *sprite, \
								t_sprite_texture_data *texture_data)
{
	texture_data->sprite_data = mlx_get_data_addr( \
								sprite->textures[sprite->current_frame], \
								&texture_data->bpp, \
								&texture_data->size_line, \
								&texture_data->endian \
								);
	texture_data->texWidth = 32;
	texture_data->texHeight = 32;
}

static void	calculate_texture_coordinates(int y, t_sprite_transform *tdata, \
			t_texture_coordinates *coords, t_sprite_texture_data *texture_data)
{
	coords->texY = (y - tdata->drawStartY) \
					* texture_data->texHeight / tdata->spriteHeight;
}

static void	draw_sprite_pixel(t_data *data, \
						t_sprite_texture_data *texture_data, \
						t_texture_coordinates *coords, int pos)
{
	char			*color;
	unsigned int	pixel_color;
	char			*dst;

	color = &texture_data->sprite_data[(coords->texY * texture_data->size_line \
									+ coords->texX * (texture_data->bpp / 8))];
	pixel_color = *(unsigned int *)color;
	if ((pixel_color & 0x00FFFFFF) != 0x000000)
	{
		dst = data->img->img_addr + pos;
		*(unsigned int *)dst = pixel_color;
	}
}

static void	draw_sprite_stripe(t_data *data, t_sprite *sprite, \
						t_sprite_transform *tdata, int stripe)
{
	t_sprite_texture_data	texture_data;
	t_texture_coordinates	coords;
	int						y;

	get_sprite_texture_data(sprite, &texture_data);
	coords.texX = (stripe - tdata->drawStartX) \
					* texture_data.texWidth / tdata->spriteWidth;
	y = tdata->drawStartY;
	while (y < tdata->drawEndY)
	{
		int pos = y * data->img->line_length \
				+ stripe * (data->img->bits_per_pixel / 8);
		calculate_texture_coordinates(y, tdata, &coords, &texture_data);
		draw_sprite_pixel(data, &texture_data, &coords, pos);
		y++;
	}
}

void	draw_sprites(t_data *data)
{
	t_sprite_transform	tdata;
	t_sprite			*sprite;
	int					stripe;
	int					y;

	if (!data || data->num_sprites == 0)
		return ;
	ft_memset(&tdata, 0, sizeof(t_sprite_transform));
	y = 0;
	sort_sprites(data, 0, 0);
	while (y < data->total_sprites)
	{
		sprite = &data->sprites[y];
		calculate_sprite_transform(data, sprite, &tdata);
		if (tdata.transformY <= 0)
		{
			y++;
			continue;
		}
		stripe = tdata.drawStartX;
		while (stripe < tdata.drawEndX)
		{
			if (stripe >= 0 && stripe < data->game->sizex
				&& tdata.transformY < data->game->zbuffer[stripe])
			{
				draw_sprite_stripe(data, sprite, &tdata, stripe);
				data->game->zbuffer[stripe] = tdata.transformY;
			}
			stripe++;
		}
		sprite->current_frame = (sprite->current_frame + 1) % sprite->num_frames;
		y++;
	}
}
