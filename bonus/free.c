/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roarslan <roarslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:01:21 by roarslan          #+#    #+#             */
/*   Updated: 2024/11/21 14:26:24 by roarslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	free_game_resources(t_game *game)
{
	if (game)
	{
		if (game->zbuffer)
		{
			free(game->zbuffer);
			game->zbuffer = NULL;
		}
		free(game);
		game = NULL;
	}
}

void	free_and_exit(t_data *data)
{
	if (data->map)
		free_map_resources(data->map);
	free_game_resources(data->game);
	if (data->img)
	{
		ft_destroy_img(data);
		free(data->img);
		data->img = NULL;
	}
	free_sprites(data);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	if (data->mlx)
		free(data->mlx);
	data->mlx = NULL;
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(EXIT_SUCCESS);
}

void	ft_destroy_img(t_data *data)
{
	int	i;

	i = 0;
	while (i < NBR_TEXTURES)
	{
		if (data->img->texture[i])
		{
			if (data->img->texture[i]->img_ptr)
				mlx_destroy_image(data->mlx, data->img->texture[i]->img_ptr);
			free(data->img->texture[i]);
			data->img->texture[i] = NULL;
		}
		i++;
	}
	free_sprite_textures(data, data->sprites);
}

int	ft_escape(t_data *data)
{
	if (data->img->img_addr)
		mlx_destroy_image(data->mlx, data->img->img_ptr);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	free_and_exit(data);
	return (0);
}
