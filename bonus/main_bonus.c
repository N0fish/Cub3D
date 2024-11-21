/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:47:13 by roarslan          #+#    #+#             */
/*   Updated: 2024/11/21 13:30:11 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	init_structures(t_data *data)
{
	data->mlx = NULL;
	data->win = NULL;
	data->total_sprites = 0;
	data->num_sprites = 0;
	data->sprites = NULL;
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
	data->game->zbuffer = NULL;
}

int	ft_render(t_data *data)
{
	handle_mouse_rotation(data);
	handle_movement(data);
	ft_memset(data->img->img_addr, 0, data->game->sizex
		* data->game->sizey * (data->img->bits_per_pixel / 8));
	ft_memset(data->game->zbuffer, 0, sizeof(double) * data->game->sizex);
	cast_rays(data);
	draw_sprites(data);
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img_ptr, 0, 0);
	return (0);
}

void	ft_hooks(t_data *data)
{
	mlx_hook(data->win, KeyPress, KeyPressMask, &ft_keypress, data);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, &ft_keyrelease, data);
	mlx_hook(data->win, DestroyNotify, StructureNotifyMask, &ft_escape, data);
	mlx_hook(data->win, MotionNotify, PointerMotionMask, &mouse_move, data);
	mlx_mouse_move(data->mlx, data->win, data->game->sizex / 2, \
					data->game->sizey / 2);
	mlx_loop_hook(data->mlx, &ft_render, data);
	mlx_loop(data->mlx);
}

int	launch_game(t_data *data)
{
	mlx_get_screen_size(data->mlx, &data->game->sizex, &data->game->sizey);
	data->game->zbuffer = malloc(sizeof(double) * data->game->sizex);
	if (!data->game->zbuffer)
	{
		ft_putstr_fd("Error\nFailed to allocate memory for zbuffer\n", 2);
		free_and_exit(data);
	}
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
	ft_hooks(data);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 2)
	{
		init_structures(&data);
		check_map(data.map, av[1]);
		init_sprites(&data);
		launch_game(&data);
	}
	else
		ft_putstr_fd("Error\nWrong arguents\n", STDERR_FILENO);
	return (0);
}
