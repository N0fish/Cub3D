/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:11:48 by roarslan          #+#    #+#             */
/*   Updated: 2024/11/13 21:38:02 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	get_max_len(t_map *map)
{
	int	i;

	i = 0;
	map->max_len = 0;
	while (map->map2d[i])
	{
		if ((int)ft_strlen(map->map2d[i]) > map->max_len)
			map->max_len = (int)ft_strlen(map->map2d[i]);
		i++;
	}
}

void	fill_map_helper(t_map *map, int i, int j, char *new_line)
{
	if (map->map2d[i][j] == ' ')
		new_line[j] = '1';
	else if (is_player(map->map2d[i][j]))
		new_line[j] = '0';
	else if (map->map2d[i][j] == 'X')
		new_line[j] = 'X';
	else
		new_line[j] = map->map2d[i][j];
}

void	fill_map(t_map *map)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	while (map->map2d[i])
	{
		new_line = ft_calloc(map->max_len + 1, sizeof(char));
		if (!new_line)
			return ;
		j = 0;
		while (map->map2d[i][j])
		{
			fill_map_helper(map, i, j, new_line);
			j++;
		}
		while (j < map->max_len)
			new_line[j++] = '1';
		new_line[j] = '\0';
		free(map->map2d[i]);
		map->map2d[i++] = new_line;
	}
}

char	*delete_spaces(char *str)
{
	char	*dest;
	int		i;
	int		j;

	dest = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			dest[j++] = str[i];
		i++;
	}
	dest[j] = '\0';
	free(str);
	return (dest);
}
