/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roarslan <roarslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:14:38 by roarslan          #+#    #+#             */
/*   Updated: 2024/10/30 16:15:16 by roarslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	player_init_helper1(double dx, double dy, t_data *data)
{
	data->game->dirx = dx;
	data->game->diry = dy;
}

void	player_init_helper2(double px, double py, t_data *data)
{
	data->game->planex = px;
	data->game->planey = py;
}

void	player_init(t_data *data)
{
	if (data->map->pl_dir == 'N')
	{
		player_init_helper1(0, -1, data);
		player_init_helper2(0.66, 0, data);
	}
	else if (data->map->pl_dir == 'S')
	{
		player_init_helper1(0, 1, data);
		player_init_helper2(-0.66, 0, data);
	}	
	else if (data->map->pl_dir == 'E')
	{
		player_init_helper1(1, 0, data);
		player_init_helper2(0, 0.66, data);
	}	
	else if (data->map->pl_dir == 'W')
	{
		player_init_helper1(-1, 0, data);
		player_init_helper2(0, -0.66, data);
	}
	data->game->sizex = data->game->sizex / 2;
	data->game->sizey = data->game->sizey / 2;
}
