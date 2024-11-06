/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 22:47:01 by algultse          #+#    #+#             */
/*   Updated: 2024/11/05 22:49:32 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

# include "includes.h"

# define MOUSE_SENSITIVITY 0.002

typedef struct s_data	t_data;

typedef struct s_minimap
{
	int	map_size;
	int	map_scale;
	int	offset_x;
	int	offset_y;
	int	player_x;
	int	player_y;
}	t_minimap;

//minimap
void	draw_minimap(t_data *data);
void	draw_map_blocks(t_data *data, t_minimap *minimap);
void	draw_block_pixel(t_data *data, int pixel_x, int pixel_y, int color);

#endif
