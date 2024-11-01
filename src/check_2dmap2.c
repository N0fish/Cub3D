/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2dmap2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roarslan <roarslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:09:56 by roarslan          #+#    #+#             */
/*   Updated: 2024/10/30 15:10:22 by roarslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes.h"

int	is_ones_and_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1' && str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	check_closed(char *str)
{
	int	i;
	int	end;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (!str[i] || str[i] != '1')
		return (0);
	end = ft_strlen(str) - 1;
	while (end >= 0 && str[end] == ' ')
		end--;
	if (end < 0 || str[end] != '1')
		return (0);
	return (1);
}

int	is_map_closed(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		if (ft_strlen(map[i]) == 0 || (map[i][0] == '\n' && map[i][1] == '\0')
			|| !check_closed(map[i]))
			return (0);
		while (map[i][j])
		{
			if (map[i][j] == ' ' && !check_around(map, i, j, " 1"))
				return (0);
			else if (map[i][j] == '0' && !check_around(map, i, j, "NSEW10"))
				return (0);
			j++;
		}
		i++;
	}
	if (!is_ones_and_spaces(map[0]) || !is_ones_and_spaces(map[i - 1]))
		return (0);
	return (1);
}

int	small_check_map(t_map *map, char *prev_line)
{
	if (ft_strncmp(prev_line, "\n", 2) != 0)
	{
		ft_putstr_fd("Error\nInvalid map configuration\n", 2);
		return (free(prev_line), 0);
	}
	free(prev_line);
	if (!check_valid_chars(map->map2d, map))
	{
		ft_putstr_fd("Error\nInvalid characters in map\n", STDERR_FILENO);
		return (0);
	}
	if (!is_map_closed(map->map2d))
	{
		ft_putstr_fd("Error\nMap is not closed\n", STDERR_FILENO);
		return (0);
	}
	return (1);
}

void	small_check_map_error(t_map *map)
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
	free(map);
	map = NULL;
	exit(EXIT_FAILURE);
}
