/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roarslan <roarslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:09:40 by roarslan          #+#    #+#             */
/*   Updated: 2024/11/04 16:05:52 by roarslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes.h"

int	check_rgb(char **rgb)
{
	int	i;

	i = 0;
	while (rgb[i])
	{
		if (!ft_isnum(rgb[i]) || ft_strlen(rgb[i]) > 3)
			return (0);
		i++;
	}
	return (1);
}

int	check_rgb_format(char *str, int *color)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	rgb = ft_split(str, ',');
	if (!rgb || tab_size(rgb) != 3 || !check_rgb(rgb))
		return (free_tab(rgb), 0);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	free_tab(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);
	*color = (r << 16) | (g << 8) | b;
	return (1);
}
