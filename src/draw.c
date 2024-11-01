/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roarslan <roarslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:13:00 by roarslan          #+#    #+#             */
/*   Updated: 2024/10/30 15:22:10 by roarslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes.h"

void	draw_ceiling(t_game *game, int x)
{
	int		y;
	int		color;
	char	*pixel;

	y = 0;
	color = game->c_color;
	while (y < game->drawstart)
	{
		pixel = game->data->img->img_addr
			+ (y * game->data->img->line_length
				+ x * (game->data->img->bits_per_pixel / 8));
		*(unsigned int *)pixel = color;
		y++;
	}
}

void	draw_floor(t_game *game, int x)
{
	int		color;
	int		y;
	char	*pixel;

	y = game->drawend;
	color = game->f_color;
	while (y < game->sizey)
	{
		pixel = game->data->img->img_addr
			+ (y * game->data->img->line_length
				+ x * (game->data->img->bits_per_pixel / 8));
		*(unsigned int *)pixel = color;
		y++;
	}
}

int	get_cardinal_dir(t_game *game)
{
	if (game->side == 1)
	{
		if (game->raydiry > 0)
			return (SOUTH);
		else
			return (NORTH);
	}
	else
	{
		if (game->raydirx > 0)
			return (EAST);
		else
			return (WEST);
	}
}

void	draw_wall_helper(t_game *game, int dir)
{
	if (game->side == 0)
		game->wallx = game->posy + game->perpwalldist * game->raydiry;
	else
		game->wallx = game->posx + game->perpwalldist * game->raydirx;
	game->wallx -= floor(game->wallx);
	game->texx = (int)(game->wallx
			* (double)game->data->img->texture[dir]->width);
	if ((game->side == 0 && game->raydirx > 0)
		|| (game->side == 1 && game->raydiry < 0))
		game->texx = game->data->img->texture[dir]->width - game->texx - 1;
	game->step = 1.0 * game->data->img->texture[dir]->height / game->lineheigth;
	game->texpos = (game->drawstart - game->sizey / 2
			+ game->lineheigth / 2) * game->step;
}

void	draw_column(t_game *game, int x)
{
	int				y;
	char			*pixel;
	int				dir;
	unsigned int	color;

	draw_ceiling(game, x);
	y = game->drawstart;
	dir = get_cardinal_dir(game);
	draw_wall_helper(game, dir);
	while (y < game->drawend)
	{
		game->texy = (int)game->texpos
			& (game->data->img->texture[dir]->height - 1);
		game->texpos += game->step;
		color = *(unsigned int *)(game->data->img->texture[dir]->img_addr
				+ (game->texy * game->data->img->texture[dir]->line_length
					+ game->texx
					* (game->data->img->texture[dir]->bits_per_pixel / 8)));
		pixel = game->data->img->img_addr
			+ (y * game->data->img->line_length
				+ x * (game->data->img->bits_per_pixel / 8));
		*(unsigned int *)pixel = color;
		y++;
	}
	draw_floor(game, x);
}
