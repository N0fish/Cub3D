/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite_calculate.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roarslan <roarslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:00:18 by algultse          #+#    #+#             */
/*   Updated: 2024/11/19 15:37:57 by roarslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

static void	calculate_sprite_position(t_data *data, t_sprite *sprite, \
								t_sprite_transform *tdata)
{
	tdata->spritex = sprite->x - data->game->posx;
	tdata->spritey = sprite->y - data->game->posy;
}

static void	calculate_inverse_and_transform(t_data *data, \
									t_sprite_transform *tdata)
{
	double	invdet;

	invdet = 1.0 / (data->game->planex * data->game->diry \
					- data->game->dirx * data->game->planey \
					);
	tdata->transformx = invdet \
				* (data->game->diry * tdata->spritex \
								- data->game->dirx * tdata->spritey \
								);
	tdata->transformy = invdet \
				* (-data->game->planey * tdata->spritex \
								+ data->game->planex * tdata->spritey \
								);
}

static void	calculate_sprite_screen(t_data *data, t_sprite_transform *tdata)
{
	if (tdata->transformy <= 0)
		return ;
	tdata->spritescreenx = (int)((data->game->sizex / 2) \
							* (1 + tdata->transformx / tdata->transformy));
	tdata->spriteheight = ft_abs((int)(data->game->sizey / tdata->transformy));
	tdata->spritewidth = tdata->spriteheight;
}

static void	calculate_draw_boundaries(t_data *data, t_sprite_transform *tdata)
{
	tdata->drawstarty = (data->game->sizey / 2) - (tdata->spriteheight / 3);
	if (tdata->drawstarty < 0)
		tdata->drawstarty = 0;
	tdata->drawendy = tdata->drawstarty + tdata->spriteheight;
	if (tdata->drawendy >= data->game->sizey)
		tdata->drawendy = data->game->sizey - 1;
	tdata->drawstartx = tdata->spritescreenx - tdata->spritewidth / 2;
	tdata->drawendx = tdata->spritescreenx + tdata->spritewidth / 2;
	if (tdata->drawstartx < -tdata->spritewidth)
		tdata->drawstartx = 0;
	if (tdata->drawendx >= data->game->sizex + tdata->spritewidth)
		tdata->drawendx = data->game->sizex - 1;
}

void	calculate_sprite_transform(t_data *data, t_sprite *sprite, \
								t_sprite_transform *tdata)
{
	calculate_sprite_position(data, sprite, tdata);
	calculate_inverse_and_transform(data, tdata);
	calculate_sprite_screen(data, tdata);
	calculate_draw_boundaries(data, tdata);
}
