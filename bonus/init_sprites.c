/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roarslan <roarslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:21:03 by algultse          #+#    #+#             */
/*   Updated: 2024/11/19 15:25:57 by roarslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

static char	*build_texture_path(int frame_index)
{
	char	*path;
	char	*frame_str;
	char	*final_path;

	frame_str = ft_itoa(frame_index);
	if (!frame_str)
		return (NULL);
	path = ft_strjoin_b("./sprite/Fire-Animation-", frame_str);
	free(frame_str);
	if (!path)
		return (NULL);
	final_path = ft_strjoin_b(path, ".xpm");
	free(path);
	return (final_path);
}

static void	load_sprite_texture(t_data *data, int sprite_index, int frame_index)
{
	char	*path;

	path = build_texture_path(frame_index);
	if (!path)
	{
		ft_putstr_fd("Error\nFailed to allocate memory for texture path\n", 2);
		free_and_exit(data);
	}
	data->sprites[sprite_index].textures[frame_index] = mlx_xpm_file_to_image \
		(data->mlx, \
		path, \
		&data->img->texture[0]->width, \
		&data->img->texture[0]->height \
		);
	free(path);
	if (!data->sprites[sprite_index].textures[frame_index])
		ft_xpm_error(data);
	if (frame_index + 1 < data->sprites[sprite_index].num_frames)
		load_sprite_texture(data, sprite_index, frame_index + 1);
}

static void	allocate_sprites_array(t_data *data)
{
	data->sprites = (t_sprite *)malloc(sizeof(t_sprite) * data->total_sprites);
	if (!data->sprites)
	{
		ft_putstr_fd("Error\nFailed to allocate memory for sprites\n", 2);
		free_and_exit(data);
	}
}

static void	initialize_sprite(t_data *data, int index)
{
	data->sprites[index].textures = NULL;
	data->sprites[index].num_frames = 14;
	data->sprites[index].current_frame = 0;
	data->sprites[index].textures = malloc(sizeof(void *) \
								* data->sprites[index].num_frames);
	if (!data->sprites[index].textures)
	{
		ft_putstr_fd \
			("Error\nFailed to allocate memory for sprite textures\n", 2 \
			);
		free_and_exit(data);
	}
}

void	init_sprites(t_data *data)
{
	int	i;

	data->mlx = mlx_init();
	if (!data->mlx)
	{
		ft_putstr_fd("Error\nMLX fail\n", 2);
		free_and_exit(data);
		return ;
	}
	allocate_sprites_array(data);
	i = 0;
	while (i < data->total_sprites)
	{
		initialize_sprite(data, i);
		load_sprite_texture(data, i, 0);
		i++;
	}
	handle_map_sprites(data->map);
}
