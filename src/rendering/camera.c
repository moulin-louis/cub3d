/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 12:54:37 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/05 21:36:25 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define ROTSPEED 1.1

void	camera2(mlx_key_data_t key, t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	if (key.key == MLX_KEY_D && ((key.action == MLX_REPEAT
				|| key.action == MLX_PRESS)))
		data->pos_y = data->pos_y * 1.1;
	if (key.key == MLX_KEY_A && ((key.action == MLX_REPEAT
				|| key.action == MLX_PRESS)))
		data->pos_y = data->pos_y * 0.9;
	if (key.key == MLX_KEY_RIGHT && ((key.action == MLX_REPEAT
				|| key.action == MLX_PRESS)))
	{
		old_dir_x = data->dir_x;
		data->dir_x = data->dir_x * cos(-ROTSPEED) - data->dir_y
			* sin(-ROTSPEED);
		data->dir_y = old_dir_x * sin(-ROTSPEED) + data->dir_y
			* cos(-ROTSPEED);
		old_plane_x = data->plane_x;
		data->plane_x = data->plane_x * cos(-ROTSPEED) - data->plane_y
			* sin(-ROTSPEED);
		data->plane_y = old_plane_x * sin(-ROTSPEED) + data->plane_y
			* cos(-ROTSPEED);
	}
}

void	camera(mlx_key_data_t key, void *ptr)
{
	t_data	*data;
	double	old_dir_x;
	double	old_plane_x;

	data = (t_data *)ptr;
	if (key.key == MLX_KEY_W && (key.action == MLX_REPEAT
			|| key.action == MLX_PRESS))
		data->pos_x = data->pos_x * 0.9;
	if (key.key == MLX_KEY_S && (key.action == MLX_REPEAT
			|| key.action == MLX_PRESS))
		data->pos_x = data->pos_x * 1.1;
	if (key.key == MLX_KEY_LEFT && ((key.action == MLX_REPEAT
				|| key.action == MLX_PRESS)))
	{
		old_dir_x = data->dir_x;
		data->dir_x = data->dir_x * cos(ROTSPEED) - data->dir_y * sin(ROTSPEED);
		data->dir_y = old_dir_x * sin(ROTSPEED) + data->dir_y * cos(ROTSPEED);
		old_plane_x = data->plane_x;
		data->plane_x = data->plane_x * cos(ROTSPEED) - data->plane_y
			* sin(ROTSPEED);
		data->plane_y = old_plane_x * sin(ROTSPEED) + data->plane_y
			* cos(ROTSPEED);
	}
	camera2(key, data);
}
