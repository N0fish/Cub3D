/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:00:13 by roarslan          #+#    #+#             */
/*   Updated: 2024/11/15 18:34:12 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

//это для вращения камеры скурсором
void	rotate_camera(t_data *data, int delta_x)
{
	double	rotation_speed;
	t_game	*game;

	game = data->game;
	rotation_speed = delta_x * MOUSE_SENSITIVITY;
	if (rotation_speed > 0.05)
		rotation_speed = 0.05;
	else if (rotation_speed < -0.05)
		rotation_speed = -0.05;
	game->olddirx = game->dirx;
	game->oldplanex = game->planex;
	game->dirx = game->dirx * cos(rotation_speed) \
					- game->diry * sin(rotation_speed);
	game->diry = game->olddirx * sin(rotation_speed) \
					+ game->diry * cos(rotation_speed);
	game->planex = game->planex * cos(rotation_speed) \
					- game->planey * sin(rotation_speed);
	game->planey = game->oldplanex * sin(rotation_speed) \
					+ game->planey * cos(rotation_speed);
}

//положения курсора
//static int - нужна для отслеживания предыдущего положения
int	calculate_mouse_delta(int x)
{
	static int	prev_mouse_x;
	int			delta_x;

	if (prev_mouse_x == 0)
	{
		prev_mouse_x = x;
		return (0);
	}
	delta_x = x - prev_mouse_x;
	prev_mouse_x = x;
	return (delta_x);
}

int	mouse_move(int x, int y, t_data *data)
{
	int	delta_x;

	(void)y;
	delta_x = calculate_mouse_delta(x);
	if (ft_abs(delta_x) < 3)
		return (0);
	rotate_camera(data, delta_x);
	return (0);
}

/*
твоя функция, базу которой я успользовала
int	mouse_move(int x, int y, t_data *data)
{
	int	center_x;
	int	delta_x;
	t_game	*game;

	(void)y;
	game = data->game;
	center_x = game->sizex / 2;
	delta_x = x - center_x;
	if (abs(delta_x) > 1)
	{
		game->rot_speed = delta_x * MOUSE_SENSITIVITY;
		game->olddirx = game->dirx;
		game->oldplanex = game->planex;
		game->dirx = game->dirx * cos(game->rot_speed) 
						- game->diry * sin(game->rot_speed);
		game->diry = game->olddirx * sin(game->rot_speed) 
						+ game->diry * cos(game->rot_speed);
		game->planex = game->planex * cos(game->rot_speed) 
						- game->planey * sin(game->rot_speed);
		game->planey = game->oldplanex * sin(game->rot_speed) 
						+ game->planey * cos(game->rot_speed);		
		mlx_mouse_move(data->mlx, data->win, center_x, game->sizey / 2);
	}
	return (0);
}
*/