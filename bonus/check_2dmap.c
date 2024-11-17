/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_2dmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:32:31 by roarslan          #+#    #+#             */
/*   Updated: 2024/11/13 15:13:23 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	get_2dmap_info(t_map *map, char *file)
{
	int		fd;
	char	*line;
	char	*prev_line;

	fd = open(file, O_RDONLY);
	prev_line = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (!is_map_assets(line) && !is_textures(line) && line[0] != '\n')
		{
			get_map2d(line, map, fd);
			break ;
		}
		if (prev_line)
			free(prev_line);
		prev_line = ft_strdup_to_n(line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!small_check_map(map, prev_line))
		free_and_exit(map->data);
}

void	get_map2d(char *line, t_map *map, int fd)
{
	int	i;

	if (!line || fd < 0)
		return ;
	i = 0;
	while (line)
	{
		map->map2d[i] = ft_strdup_to_n(line);
		i++;
		free(line);
		line = get_next_line(fd);
	}
	map->map2d[i] = NULL;
}

int	is_player(char c)
{
	if (c == 'N' || c == 'S'
		|| c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	is_valid_char(t_map *map, char **tab, int i, int j)
{
	if (tab[i][j] != ' ' && tab[i][j] != '1' && tab[i][j] != '0' \
		&& tab[i][j] != 'N' && tab[i][j] != 'S' \
		&& tab[i][j] != 'E' && tab[i][j] != 'W' \
		&& tab[i][j] != 'X')
		return (0);
	if (is_player(tab[i][j]))
	{
		if (!check_around(tab, i, j, "01"))
			return (0);
		map->data->game->posy = i + 0.5;
		map->data->game->posx = j + 0.5;
	}
	return (1);
}

int	check_valid_chars(char **map, t_map *tmap)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_player(map[i][j]))
			{
				tmap->pl_dir = map[i][j];
				count++;
			}
			if (!is_valid_char(tmap, map, i, j))
				return (0);
			j++;
		}
		i++;
	}
	if (count != 1)
		return (0);
	return (1);
}
