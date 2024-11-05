/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roarslan <roarslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:43:29 by roarslan          #+#    #+#             */
/*   Updated: 2024/10/30 16:16:16 by roarslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	get_map_images2(char *str, t_map *map)
{
	if (ft_strncmp(str, "WE", 2) == 0)
	{
		if (map->west_wall == NULL)
			map->west_wall = ft_substr(str, 3, ft_strlen(str) - 4);
		else
			map->west_wall = ft_strjoin(map->west_wall, "INVALID\n");
	}
	else if (ft_strncmp(str, "EA", 2) == 0)
	{
		if (map->east_wall == NULL)
			map->east_wall = ft_substr(str, 3, ft_strlen(str) - 4);
		else
			map->east_wall = ft_strjoin(map->east_wall, "INVALID\n");
	}
}

void	get_map_images(char	*str, t_map *map)
{
	if (ft_strncmp(str, "NO", 2) == 0)
	{
		if (map->north_wall == NULL)
			map->north_wall = ft_substr(str, 3, ft_strlen(str) - 4);
		else
			map->north_wall = ft_strjoin(map->north_wall, "INVALID\n");
	}
	else if (ft_strncmp(str, "SO", 2) == 0)
	{
		if (map->south_wall == NULL)
			map->south_wall = ft_substr(str, 3, ft_strlen(str) - 4);
		else
			map->south_wall = ft_strjoin(map->south_wall, "INVALID\n");
	}
	get_map_images2(str, map);
}

int	small_image_check(t_map *map)
{
	if (!map->east_wall || !map->west_wall
		|| !map->north_wall || !map->south_wall)
		return (0);
	map->east_wall = delete_spaces(map->east_wall);
	map->west_wall = delete_spaces(map->west_wall);
	map->north_wall = delete_spaces(map->north_wall);
	map->south_wall = delete_spaces(map->south_wall);
	if ((!check_extension(map->north_wall)
			|| !check_extension(map->south_wall)
			|| !check_extension(map->east_wall)
			|| !check_extension(map->west_wall)))
		return (0);
	if (open(map->north_wall, O_RDONLY) == -1
		|| open(map->south_wall, O_RDONLY) == -1
		|| open(map->west_wall, O_RDONLY) == -1
		|| open(map->east_wall, O_RDONLY) == -1)
		return (0);
	return (1);
}

void	get_assets_info(t_map *map, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (is_map_assets(line))
			get_map_images(line, map);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (line)
		free(line);
	if (!small_image_check(map))
	{
		ft_putstr_fd("Error\nInvalid asset\n", STDERR_FILENO);
		free_and_exit(map->data);
	}
}

int	check_extension(char *file_name)
{
	int	len;

	if (!file_name)
		return (0);
	len = ft_strlen(file_name);
	if (len < 5)
		return (0);
	if (file_name[len - 4] == '.' && file_name[len - 3] == 'x'
		&& file_name[len - 2] == 'p' && file_name[len - 1] == 'm')
		return (1);
	return (0);
}
