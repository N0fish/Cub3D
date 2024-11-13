/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:10:20 by roarslan          #+#    #+#             */
/*   Updated: 2024/11/13 15:08:32 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	cast_rays(t_data *data)
{
	int		i;
	t_game	*game;

	game = data->game;
	i = 0;
	while (i < game->sizex)
	{
		game->camerax = 2 * i / (double)game->sizex - 1;
		game->raydirx = game->dirx + game->planex * game->camerax;
		game->raydiry = game->diry + game->planey * game->camerax;
		game->deltadistx = fabs(1 / game->raydirx);
		game->deltadisty = fabs(1 / game->raydiry);
		calculate_sidedist(game);
		ft_dda(game);
		get_lines_height(game);
		if (i >= 0 && i < game->sizex)
			game->zbuffer[i] = game->perpwalldist;
		draw_column(game, i);
		i++;
	}
}

void	calculate_sidedist(t_game *game)
{
	game->mapx = (int)game->posx;
	game->mapy = (int)game->posy;
	if (game->raydirx < 0)
	{
		game->stepx = -1;
		game->sidedistx = (game->posx - game->mapx) * game->deltadistx;
	}
	else
	{
		game->stepx = 1;
		game->sidedistx = (game->mapx + 1.0 - game->posx) * game->deltadistx;
	}
	if (game->raydiry < 0)
	{
		game->stepy = -1;
		game->sidedisty = (game->posy - game->mapy) * game->deltadisty;
	}
	else
	{
		game->stepy = 1;
		game->sidedisty = (game->mapy + 1.0 - game->posy) * game->deltadisty;
	}
}

void	ft_dda(t_game *game)
{
	game->hit = 0;
	while (game->hit == 0)
	{
		if (game->sidedistx < game->sidedisty)
		{
			game->sidedistx += game->deltadistx;
			game->mapx += game->stepx;
			game->side = 0;
		}
		else
		{
			game->sidedisty += game->deltadisty;
			game->mapy += game->stepy;
			game->side = 1;
		}
		if (game->data->map->map2d[game->mapy][game->mapx] == '1')
			game->hit = 1;
	}
	if (game->side == 0)
		game->perpwalldist = (game->sidedistx - game->deltadistx);
	else
		game->perpwalldist = (game->sidedisty - game->deltadisty);
}

void	get_lines_height(t_game *game)
{
	game->lineheigth = (int)(game->sizey / game->perpwalldist);
	game->drawstart = -(game->lineheigth / 2) + (game->sizey / 2);
	if (game->drawstart < 0)
		game->drawstart = 0;
	game->drawend = (game->lineheigth / 2) + (game->sizey / 2);
	if (game->drawend >= game->sizey)
		game->drawend = game->sizey;
}
