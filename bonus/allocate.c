/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roarslan <roarslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:10:32 by algultse          #+#    #+#             */
/*   Updated: 2024/11/19 15:12:44 by roarslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

static void	allocate_map(t_data *data)
{
	data->map = (t_map *)malloc(sizeof(t_map));
	if (!data->map)
	{
		ft_putstr_fd("Error\nMalloc failed\n", 2);
		exit(EXIT_FAILURE);
	}
	data->map->data = data;
}

static void	allocate_game(t_data *data)
{
	data->game = (t_game *)malloc(sizeof(t_game));
	if (!data->game)
	{
		free(data->map);
		ft_putstr_fd("Error\nMalloc failed\n", 2);
		free_and_exit(data);
	}
	// data->game->sizex = WIDTH;
	// data->game->sizey = HEIGHT;
	// data->game->zbuffer = malloc(sizeof(double) * data->game->sizex);
	// if (!data->game->zbuffer)
	// {
	// 	ft_putstr_fd("Error\nFailed to allocate memory for zbuffer\n", 2);
	// 	free_and_exit(data);
	// }
}

static void	allocate_img(t_data *data)
{
	data->img = (t_img *)malloc(sizeof(t_img));
	if (!data->img)
	{
		free(data->map);
		free(data->game);
		ft_putstr_fd("Error\nMalloc failed\n", 2);
		free_and_exit(data);
	}
	data->img->img_ptr = NULL;
	data->img->img_addr = NULL;
}

static void	allocate_texturess(t_data *data)
{
	int	i;

	i = 0;
	while (i < NBR_TEXTURES)
	{
		data->img->texture[i] = malloc(sizeof(t_texture));
		if (!data->img->texture[i])
		{
			ft_putstr_fd("Error\nMalloc failed\n", 2);
			free(data->map);
			free(data->game);
			free(data->img);
			free_and_exit(data);
		}
		data->img->texture[i]->img_ptr = NULL;
		i++;
	}
}

void	allocate_structures(t_data *data)
{
	allocate_map(data);
	allocate_game(data);
	allocate_img(data);
	allocate_texturess(data);
}
