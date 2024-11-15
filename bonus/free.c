/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roarslan <roarslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:01:21 by roarslan          #+#    #+#             */
/*   Updated: 2024/10/30 16:16:54 by roarslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	free_images(t_map *map)
{
	if (map->east_wall)
	{
		free(map->east_wall);
		map->east_wall = NULL;
	}
	if (map->west_wall)
	{
		free(map->west_wall);
		map->west_wall = NULL;
	}
	if (map->north_wall)
	{
		free(map->north_wall);
		map->north_wall = NULL;
	}
	if (map->south_wall)
	{
		free(map->south_wall);
		map->south_wall = NULL;
	}
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static void	free_map_resources(t_map *map)
{
	if (map->floor)
	{
		free(map->floor);
		map->floor = NULL;
	}
	if (map->ceiling)
	{
		free(map->ceiling);
		map->ceiling = NULL;
	}
	if (map->map2d)
	{
		free_tab(map->map2d);
		map->map2d = NULL;
	}
	free_images(map);
	if (map)
		free(map);
	map = NULL;
}

void	free_and_exit(t_data *data)
{
	if (data->map)
		free_map_resources(data->map);
	if (data->game)
	{
		if (data->game->zbuffer)
		{
			free(data->game->zbuffer);
			data->game->zbuffer = NULL;
		}
		free(data->game);
		data->game = NULL;
	}
	if (data->img)
	{
		free(data->img);
		data->img = NULL;
	}
	free_sprites(data);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
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
		}
		i++;
	}
}

int	ft_escape(t_data *data)
{
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	ft_destroy_img(data);
	if (data->img->img_addr)
		mlx_destroy_image(data->mlx, data->img->img_ptr);
	free_and_exit(data);
	return (0);
}
