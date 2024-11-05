/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:47:13 by roarslan          #+#    #+#             */
/*   Updated: 2024/11/05 22:55:30 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	init_structures(t_data *data)
{
	data->mlx = NULL;
	data->win = NULL;
	allocate_structures(data);
	data->map->map2d = NULL;
	data->map->data = data;
	data->game->data = data;
	data->map->ceiling = NULL;
	data->map->floor = NULL;
	data->map->east_wall = NULL;
	data->map->west_wall = NULL;
	data->map->north_wall = NULL;
	data->map->south_wall = NULL;
	data->img->img_addr = NULL;
	data->keys.w = 0;
	data->keys.a = 0;
	data->keys.s = 0;
	data->keys.d = 0;
	data->keys.left = 0;
	data->keys.right = 0;
}

int	ft_render(t_data *data)
{
	handle_movement(data);
	ft_memset(data->img->img_addr, 0, data->game->sizex
		* data->game->sizey * (data->img->bits_per_pixel / 8));
	cast_rays(data);
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img_ptr, 0, 0);
	return (0);
}

int	launch_game(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (ft_putstr_fd("Error\nMLX fail\n", 2), free_and_exit(data), 0);
	mlx_get_screen_size(data->mlx, &data->game->sizex, &data->game->sizey);
	ft_xpm_to_image(data);
	player_init(data);
	data->win = mlx_new_window(data->mlx, data->game->sizex, \
		data->game->sizey, "Cub3D");
	if (!data->win)
	{
		ft_putstr_fd("Error\nMXL fail\n", STDERR_FILENO);
		ft_destroy_img(data);
		mlx_destroy_image(data->mlx, data->img->img_ptr);
		free(data->mlx);
		free_and_exit(data);
		return (0);
	}
	mlx_hook(data->win, KeyPress, KeyPressMask, &ft_keypress, data);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, &ft_keyrelease, data);
	mlx_hook(data->win, DestroyNotify, StructureNotifyMask, &ft_escape, data);
	mlx_loop_hook(data->mlx, &ft_render, data);
	mlx_loop(data->mlx);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 2)
	{
		init_structures(&data);
		check_map(data.map, av[1]);
		launch_game(&data);
	}
	else
		ft_putstr_fd("Error\nWrong arguents\n", STDERR_FILENO);
	return (0);
}
