/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roarslan <roarslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:27:04 by algultse          #+#    #+#             */
/*   Updated: 2024/11/19 16:19:08 by roarslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	free_sprite_textures(t_data *data, t_sprite *sprite)
{
	int	j;

	if (!sprite->textures)
		return ;
	j = 0;
	while (j < sprite->num_frames)
	{
		if (sprite->textures[j])
		{
			mlx_destroy_image(data->mlx, sprite->textures[j]);
			sprite->textures[j] = NULL;
		}
		j++;
	}
	free(sprite->textures);
	sprite->textures = NULL;
}

void	free_sprites(t_data *data)
{
	int	i;

	if (!data || !data->sprites)
		return ;
	i = 0;
	while (i < data->num_sprites)
	{
		free_sprite_textures(data, &data->sprites[i]);
		i++;
	}
	if (data->sprites)
		free(data->sprites);
	data->sprites = NULL;
}

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

void	free_map_resources(t_map *map)
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
