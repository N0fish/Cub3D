/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:27:04 by algultse          #+#    #+#             */
/*   Updated: 2024/11/15 19:30:42 by algultse         ###   ########.fr       */
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
