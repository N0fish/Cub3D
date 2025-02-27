/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roarslan <roarslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:14:49 by algultse          #+#    #+#             */
/*   Updated: 2024/11/19 15:40:41 by roarslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	calculate_texture_coordinates(int y, t_sprite_transform *tdata, \
			t_texture_coordinates *coords, t_sprite_texture_data *texture_data)
{
	coords->texy = (y - tdata->drawstarty) \
					* texture_data->texheight / tdata->spriteheight;
}

void	handle_map_sprites(t_map *map)
{
	int			x;
	int			y;
	t_sprite	*sprite;

	y = 0;
	while (map->map2d[y])
	{
		x = 0;
		while (map->map2d[y][x])
		{
			if (map->map2d[y][x] == 'X')
			{
				sprite = &map->data->sprites[map->data->num_sprites];
				sprite->x = x + 0.5;
				sprite->y = y + 0.5;
				map->data->num_sprites++;
			}
			x++;
		}
		y++;
	}	
}

void	handle_sprite(char *line, int i, t_map *map)
{
	int			j;
	t_sprite	*sprite;

	j = 0;
	while (line[j])
	{
		if (line[j] == 'X')
		{
			sprite = &map->data->sprites[map->data->num_sprites];
			sprite->x = j + 0.5;
			sprite->y = i + 0.5;
			map->data->num_sprites++;
		}
		j++;
	}
}

char	*ft_strjoin_b(char const *s1, char const *s2)
{
	char	*s_dest;
	char	*p_dest;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	s_dest = malloc(sizeof(char) * (len + 1));
	if (!s_dest)
		return (NULL);
	p_dest = s_dest;
	while (*s1)
		*s_dest++ = *s1++;
	while (*s2)
		*s_dest++ = *s2++;
	*s_dest = '\0';
	return (p_dest);
}

void	sort_sprites(t_data *data, int i, int j)
{
	double		dist_i;
	double		dist_j;
	t_sprite	temp;

	i = 0;
	while (i < data->total_sprites - 1)
	{
		j = i + 1;
		while (j < data->total_sprites)
		{
			dist_i = compute_dist(data->sprites[i], data->game);
			dist_j = compute_dist(data->sprites[j], data->game);
			if (dist_i < dist_j)
			{
				temp = data->sprites[i];
				data->sprites[i] = data->sprites[j];
				data->sprites[j] = temp;
			}
			j++;
		}
		i++;
	}
}
