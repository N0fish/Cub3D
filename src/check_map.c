/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roarslan <roarslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:56:37 by roarslan          #+#    #+#             */
/*   Updated: 2024/10/30 16:11:45 by roarslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes.h"

int	check_open(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	check_name(char *file)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (file[i] != '\0')
	{
		if (file[i] == '.')
		{
			count++;
			if (count > 1)
				return (0);
			if (file[i + 1] == 'c' && file[i + 2] == 'u'
				&& file[i + 3] == 'b' && file[i + 4] == '\0')
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (0);
}

void	ft_get_size_malloc(t_map *map)
{
	map->map2d = ft_calloc(map->size + 1, sizeof(char *));
	if (!map->map2d)
	{
		ft_putstr_fd("Error\nMalloc failed\n", STDERR_FILENO);
		free_images(map);
		if (map->floor)
			free(map->floor);
		if (map->ceiling)
			free(map->ceiling);
		free(map);
		exit(EXIT_FAILURE);
	}
}

void	get_map_size(t_map *map, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	map->size = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!is_map_assets(line) && !is_textures(line)
			&& line[0] != '\n')
		{
			while (line)
			{
				map->size++;
				free(line);
				line = get_next_line(fd);
			}
		}
		if (line)
			free(line);
		line = get_next_line(fd);
	}
	close(fd);
	ft_get_size_malloc(map);
}

void	check_map(t_map *map, char *file)
{
	if (!check_open(file) || !check_name(file))
	{
		ft_putstr_fd("Error\nIncorrect map\n", STDERR_FILENO);
		free_and_exit(map->data);
	}
	get_assets_info(map, file);
	get_textures_info(map, file);
	get_map_size(map, file);
	if (map->size == 0)
	{
		ft_putstr_fd("Error\nInvalid map\n", STDERR_FILENO);
		free_and_exit(map->data);
	}
	get_2dmap_info(map, file);
	get_max_len(map);
	fill_map(map);
}
