/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roarslan <roarslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 21:16:25 by algultse          #+#    #+#             */
/*   Updated: 2024/11/19 15:27:30 by roarslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

double	square(double v)
{
	return (v * v);
}

double	compute_dist(t_sprite s, t_game *game)
{
	double	dx;
	double	dy;

	dx = s.x - game->posx;
	dy = s.y - game->posy;
	return (square(dx) + square(dy));
}

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

double	ft_fabs(double n)
{
	if (n < 0)
		return (-n);
	return (n);
}
