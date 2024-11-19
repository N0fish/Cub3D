/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roarslan <roarslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:01:21 by roarslan          #+#    #+#             */
/*   Updated: 2024/11/19 15:20:48 by roarslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	free_and_exit(t_data *data)
{
	if (data->map)
		free_map_resources(data->map);
	if (data->game)
		free(data->game);
	data->game = NULL;
	if (data->img)
		free(data->img);
	if (data->mlx)
		free(data->mlx);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(EXIT_SUCCESS);
}

void	ft_destroy_img(t_data *data)
{
	int	i;

	i = 0;
	while (i < NBR_TEXTURES)
	{
		if (data->img->texture[i])
		{
			if (data->img->texture[i]->img_ptr)
				mlx_destroy_image(data->mlx, data->img->texture[i]->img_ptr);
			free(data->img->texture[i]);
		}
		i++;
	}
}

int	ft_escape(t_data *data)
{
	if (data->img->img_ptr)
		mlx_destroy_image(data->mlx, data->img->img_ptr);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	ft_destroy_img(data);
	mlx_destroy_display(data->mlx);
	free_and_exit(data);
	return (0);
}
