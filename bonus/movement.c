/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roarslan <roarslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:20:06 by roarslan          #+#    #+#             */
/*   Updated: 2024/10/30 16:20:31 by roarslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int	ft_keypress(int key, t_data *data)
{
	if (key == ESC)
		ft_escape(data);
	else if (key == RIGHT)
		data->keys.right = 1;
	else if (key == LEFT)
		data->keys.left = 1;
	else if (key == UP || key == W_KEY)
		data->keys.w = 1;
	else if (key == DOWN || key == S_KEY)
		data->keys.s = 1;
	else if (key == A_KEY)
		data->keys.a = 1;
	else if (key == D_KEY)
		data->keys.d = 1;
	return (0);
}

int	ft_keyrelease(int key, t_data *data)
{
	if (key == RIGHT)
		data->keys.right = 0;
	else if (key == LEFT)
		data->keys.left = 0;
	else if (key == UP || key == W_KEY)
		data->keys.w = 0;
	else if (key == DOWN || key == S_KEY)
		data->keys.s = 0;
	else if (key == A_KEY)
		data->keys.a = 0;
	else if (key == D_KEY)
		data->keys.d = 0;
	return (0);
}

void	handle_movement(t_data *data)
{
	if (data->keys.w)
		move_forward(data);
	if (data->keys.s)
		move_backwards(data);
	if (data->keys.a)
		strafe_left(data);
	if (data->keys.d)
		strafe_right(data);
	if (data->keys.left)
		rotate(data->game, -1);
	if (data->keys.right)
		rotate(data->game, 1);
}
