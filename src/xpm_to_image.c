/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_to_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roarslan <roarslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:17:43 by roarslan          #+#    #+#             */
/*   Updated: 2024/11/21 13:56:21 by roarslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	ft_get_addr(t_data *data)
{
	int	i;

	i = 0;
	while (i < NBR_TEXTURES)
	{
		data->img->texture[i]->img_addr \
			= mlx_get_data_addr(data->img->texture[i]->img_ptr, \
			&data->img->texture[i]->bits_per_pixel, \
			&data->img->texture[i]->line_length, \
			&data->img->texture[i]->endian);
		i++;
	}
}

void	ft_xpm_error(t_data *data)
{
	ft_putstr_fd("Error\nInvalid asset\n", 2);
	mlx_destroy_image(data->mlx, data->img->img_ptr);
	ft_destroy_img(data);
	mlx_destroy_display(data->mlx);
	if (data->mlx)
		free(data->mlx);
	data->mlx = NULL;
	free_and_exit(data);
}

void	ft_xpm_to_image(t_data *data)
{
	data->img->img_ptr = mlx_new_image(data->mlx, \
		data->game->sizex, data->game->sizey);
	data->img->img_addr = mlx_get_data_addr(data->img->img_ptr, \
		&data->img->bits_per_pixel, \
		&data->img->line_length, &data->img->endian);
	data->img->texture[NORTH]->img_ptr = mlx_xpm_file_to_image(data->mlx, \
		data->map->north_wall, \
		&data->img->texture[NORTH]->width, &data->img->texture[NORTH]->height);
	data->img->texture[SOUTH]->img_ptr = mlx_xpm_file_to_image(data->mlx, \
		data->map->south_wall, \
		&data->img->texture[SOUTH]->width, &data->img->texture[SOUTH]->height);
	data->img->texture[EAST]->img_ptr = mlx_xpm_file_to_image(data->mlx, \
		data->map->east_wall, \
		&data->img->texture[EAST]->width, &data->img->texture[EAST]->height);
	data->img->texture[WEST]->img_ptr = mlx_xpm_file_to_image(data->mlx, \
		data->map->west_wall, \
		&data->img->texture[WEST]->width, &data->img->texture[WEST]->height);
	if (!data->img->texture[NORTH]->img_ptr
		|| !data->img->texture[SOUTH]->img_ptr
		|| !data->img->texture[EAST]->img_ptr
		|| !data->img->texture[WEST]->img_ptr)
		ft_xpm_error(data);
	ft_get_addr(data);
}
