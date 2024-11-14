/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:14:49 by algultse          #+#    #+#             */
/*   Updated: 2024/11/13 22:34:00 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	handle_sprite(char *line, int i, t_map *map)
{
	int			j;
	t_sprite	*sprite;

	j = 0;
	while (line[j])
	{
		if (line[j] == 'X' && map->data->num_sprites < NUM_SPRITES)
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

void	free_sprites(t_data *data)
{
	int	i;
	int	j;

	if (!data)
		return ;
	if (data->sprites)
	{
		i = 0;
		while(i < data->num_sprites)
		{
			if (data->sprites[i].textures)
			{
				j = 0;
				while (j < data->sprites[i].num_frames)
				{
					if (data->sprites[i].textures[j])
					{
						mlx_destroy_image(data->mlx, \
							data->sprites[i].textures[j]);
						data->sprites[i].textures[j] = NULL;
					}
					j++;
				}
				free(data->sprites[i].textures);
				data->sprites[i].textures = NULL;
			}
			i++;
		}
		free(data->sprites);
		data->sprites = NULL;
	}
}

/*
void update_sprites(t_data *data)
{
	for (int i = 0; i < NUM_SPRITES; i++)
	{
		t_sprite *sprite = &data->sprites[i];
		sprite->current_frame = (sprite->current_frame + 1) % sprite->num_frames;
	}
}
*/