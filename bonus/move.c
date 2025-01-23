/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roarslan <roarslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:02:46 by roarslan          #+#    #+#             */
/*   Updated: 2024/10/30 16:08:32 by roarslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	rotate(t_game *game, int i)
{
	game->olddirx = game->dirx;
	game->dirx = game->dirx * cos(ROTATION_SPEED * i)
		- game->diry * sin(ROTATION_SPEED * i);
	game->diry = game->olddirx * sin(ROTATION_SPEED * i)
		+ game->diry * cos(ROTATION_SPEED * i);
	game->oldplanex = game->planex;
	game->planex = game->planex * cos(ROTATION_SPEED * i)
		- game->planey * sin(ROTATION_SPEED * i);
	game->planey = game->oldplanex * sin(ROTATION_SPEED * i)
		+ game->planey * cos(ROTATION_SPEED * i);
}

void	move_forward(t_data *data)
{
	t_game	*game;

	game = data->game;
	if (data->map->map2d[(int)(game->posy)] \
		[(int)(game->posx + game->dirx * (MOVE_SPEED + MARGIN))] != '1')
		game->posx += game->dirx * MOVE_SPEED;
	if (data->map->map2d[(int)(game->posy
			+ game->diry * (MOVE_SPEED + MARGIN))][(int)game->posx] != '1')
		game->posy += game->diry * MOVE_SPEED;
}

void	move_backwards(t_data *data)
{
	t_game	*game;

	game = data->game;
	if (data->map->map2d[(int)(game->posy)] \
			[(int)(game->posx - game->dirx * (MOVE_SPEED + MARGIN))] != '1')
		game->posx -= game->dirx * MOVE_SPEED;
	if (data->map->map2d[(int)(game->posy - game->diry \
		* (MOVE_SPEED + MARGIN))][(int)game->posx] != '1')
		game->posy -= game->diry * MOVE_SPEED;
}

void	strafe_left(t_data *data)
{
	t_game	*game;
	double	perpdirx;
	double	perpdiry;

	game = data->game;
	perpdirx = game->diry;
	perpdiry = -game->dirx;
	if (data->map->map2d[(int)game->posy] \
			[(int)(game->posx + perpdirx * (MOVE_SPEED + MARGIN))] != '1')
		game->posx += perpdirx * MOVE_SPEED;
	if (data->map->map2d[(int)(game->posy + perpdiry \
			* (MOVE_SPEED + MARGIN))][(int)game->posx] != '1')
		game->posy += perpdiry * MOVE_SPEED;
}

void	strafe_right(t_data *data)
{
	t_game	*game;
	double	perpdirx;
	double	perpdiry;

	game = data->game;
	perpdirx = -game->diry;
	perpdiry = game->dirx;
	if (data->map->map2d[(int)game->posy] \
			[(int)(game->posx + perpdirx * (MOVE_SPEED + MARGIN))] != '1')
		game->posx += perpdirx * MOVE_SPEED;
	if (data->map->map2d[(int)(game->posy + perpdiry \
			* (MOVE_SPEED + MARGIN))][(int)game->posx] != '1')
		game->posy += perpdiry * MOVE_SPEED;
}
