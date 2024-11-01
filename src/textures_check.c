/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roarslan <roarslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:48:28 by roarslan          #+#    #+#             */
/*   Updated: 2024/10/30 16:09:56 by roarslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes.h"

int	is_textures(char *line)
{
	if (ft_strncmp(line, "F ", 2) == 0
		|| ft_strncmp(line, "C ", 2) == 0)
		return (1);
	return (0);
}

void	get_map_textures(char *str, t_map *map)
{
	if (ft_strncmp(str, "C", 1) == 0)
	{
		if (map->ceiling == NULL)
			map->ceiling = ft_substr(str, 2, ft_strlen(str) - 3);
		else
			map->ceiling = ft_strjoin(map->ceiling, "INVALID\n");
	}
	else if (ft_strncmp(str, "F", 1) == 0)
	{
		if (map->floor == NULL)
			map->floor = ft_substr(str, 2, ft_strlen(str) - 3);
		else
			map->floor = ft_strjoin(map->floor, "INVALID\n");
	}
}

int	check_commas(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
		return (0);
	return (1);
}

int	small_textures_check(t_map *map)
{
	if (!map->ceiling || !map->floor)
	{
		ft_putstr_fd("Error\nCeiling or floor texture is missing.\n", 2);
		return (0);
	}
	map->ceiling = delete_spaces(map->ceiling);
	map->floor = delete_spaces(map->floor);
	if (!check_rgb_format(map->ceiling, &map->data->game->c_color)
		|| !check_rgb_format(map->floor, &map->data->game->f_color))
	{
		ft_putstr_fd("Error\nInvalid ceiling or floor color format.\n", 2);
		return (0);
	}
	if (!check_commas(map->ceiling) || !check_commas(map->floor))
	{
		ft_putstr_fd("Error\nGet these commas out of here\n", 2);
		return (0);
	}
	return (1);
}

void	get_textures_info(t_map *map, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (is_textures(line))
			get_map_textures(line, map);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!small_textures_check(map))
		free_and_exit(map->data);
}
