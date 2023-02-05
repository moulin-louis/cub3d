/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 12:54:37 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/05 12:59:37 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	camera2(mlx_key_data_t key, t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	if (key.key == MLX_KEY_D && ((key.action == MLX_REPEAT
				|| key.action == MLX_PRESS)))
	{
		old_dir_x = data->dir_x;
		data->dir_x = data->dir_x * cos(-1.001) - data->dir_y * sin(-1.001);
		data->dir_y = old_dir_x * sin(-1.001) + data->dir_y * cos(1);
		old_plane_x = data->plane_x;
		data->plane_x = data->plane_x * cos(-1.001)
			- data->plane_y * sin(-1.001);
		data->plane_y = old_plane_x * sin(-1.001) + data->plane_y * cos(-1.001);
	}
	if (key.key == MLX_KEY_A && ((key.action == MLX_REPEAT
				|| key.action == MLX_PRESS)))
	{
		old_dir_x = data->dir_x;
		data->dir_x = data->dir_x * cos(1) - data->dir_y * sin(1);
		data->dir_y = old_dir_x * sin(1) + data->dir_y * cos(1);
		old_plane_x = data->plane_x;
		data->plane_x = data->plane_x * cos(1) - data->plane_y * sin(1);
		data->plane_y = old_plane_x * sin(1) + data->plane_y * cos(1);
	}
}

void	camera(mlx_key_data_t key, void *ptr)
{
	t_data	*data;

	data = (t_data *)ptr;
	if (key.key == MLX_KEY_W && (key.action == MLX_REPEAT
			|| key.action == MLX_PRESS))
	{
		data->pos_x += data->dir_x * 1.5;
		data->pos_y += data->dir_y * 1.5;
	}
	if (key.key == MLX_KEY_S && (key.action == MLX_REPEAT
			|| key.action == MLX_PRESS))
	{
		data->pos_x -= data->dir_x * 1.5;
		data->pos_y -= data->dir_y * 1.5;
	}
	camera2(key, data);
}
