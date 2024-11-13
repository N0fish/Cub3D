/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite_calculate.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:00:18 by algultse          #+#    #+#             */
/*   Updated: 2024/11/13 23:05:01 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

static void	calculate_sprite_position(t_data *data, t_sprite *sprite, \
								t_sprite_transform *tdata)
{
	tdata->spriteX = sprite->x - data->game->posx;
	tdata->spriteY = sprite->y - data->game->posy;
}

static void	calculate_inverse_and_transform(t_data *data, \
									t_sprite_transform *tdata)
{
	double	invDet;
	
	invDet = 1.0 / ( \
					data->game->planex * data->game->diry \
					- data->game->dirx * data->game->planey \
					);
	tdata->transformX = invDet * ( \
								data->game->diry * tdata->spriteX \
								- data->game->dirx * tdata->spriteY \
								);
	tdata->transformY = invDet * ( \
								-data->game->planey * tdata->spriteX \
								+ data->game->planex * tdata->spriteY \
								);
}

static void	calculate_sprite_screen(t_data *data, t_sprite_transform *tdata)
{
	if (tdata->transformY <= 0)
		return ;
	tdata->spriteScreenX = (int)((data->game->sizex / 2) \
							* (1 + tdata->transformX / tdata->transformY));
	tdata->spriteHeight = abs((int)(data->game->sizey / tdata->transformY));
	tdata->spriteWidth = tdata->spriteHeight;
}

static void	calculate_draw_boundaries(t_data *data, t_sprite_transform *tdata)
{
	tdata->drawStartY = (data->game->sizey / 2) - (tdata->spriteHeight / 3);
	if (tdata->drawStartY < 0)
		tdata->drawStartY = 0;
	tdata->drawEndY = tdata->drawStartY + tdata->spriteHeight;
	if (tdata->drawEndY >= data->game->sizey)
		tdata->drawEndY = data->game->sizey - 1;
	tdata->drawStartX = tdata->spriteScreenX - tdata->spriteWidth / 2;
	tdata->drawEndX = tdata->spriteScreenX + tdata->spriteWidth / 2;
	if (tdata->drawStartX < -tdata->spriteWidth)
		tdata->drawStartX = 0;
	if (tdata->drawEndX >= data->game->sizex + tdata->spriteWidth)
		tdata->drawEndX = data->game->sizex - 1;
}

void	calculate_sprite_transform(t_data *data, t_sprite *sprite, \
								t_sprite_transform *tdata)
{
	calculate_sprite_position(data, sprite, tdata);
	calculate_inverse_and_transform(data, tdata);
	calculate_sprite_screen(data, tdata);
	calculate_draw_boundaries(data, tdata);
}
