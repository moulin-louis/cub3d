/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 12:54:37 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/06 17:16:48 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define ROTSPEED 0.05
#define MOVSPEED 0.05

void	camera2(int key, t_data *data)
{
	double	old_var;

	// if (key.key == MLX_KEY_D && ((key.action == MLX_REPEAT
	// 			|| key.action == MLX_PRESS)))
	// {
	// 	data->pos_x -= data->dir_x * MOVSPEED;
	// 	data->pos_y += data->dir_y * MOVSPEED;
	// }
	// if (key.key == MLX_KEY_A && ((key.action == MLX_REPEAT
	// 			|| key.action == MLX_PRESS)))
	// {
	// 	data->pos_x -= data->dir_x * MOVSPEED;
	// 	data->pos_y -= data->dir_y * MOVSPEED;
	// }
	if (key == XK_Right)
	{
		old_var = data->dir_x;
		data->dir_x = data->dir_x * cos(-ROTSPEED) - data->dir_y
			* sin(-ROTSPEED);
		data->dir_y = old_var * sin(-ROTSPEED) + data->dir_y
			* cos(-ROTSPEED);
		old_var = data->plane_x;
		data->plane_x = data->plane_x * cos(-ROTSPEED) - data->plane_y
			* sin(-ROTSPEED);
		data->plane_y = old_var * sin(-ROTSPEED) + data->plane_y
			* cos(-ROTSPEED);
	}
}

int	camera(int key, void *ptr)
{
	t_data	*data;
	double	old_var;

	data = (t_data *)ptr;
	if (key == XK_Escape)
	{
		printf("here");
		mlx_err(data);
	}
	if (key == XK_W)
	{
		if (data->map[(int)(data->pos_x + data->dir_x * MOVSPEED)][(int)data->pos_y] == 0)
			data->pos_x += data->dir_x * MOVSPEED;
		if (data->map[(int)data->pos_x][(int)(data->pos_y + data->dir_y * MOVSPEED)] == 0)
			data->pos_y += data->dir_y * MOVSPEED;
	}
	if (key == XK_S)
	{
		if (data->map[(int)(data->pos_x - data->dir_x * MOVSPEED)][(int)data->pos_y] == 0)
			data->pos_x -= data->dir_x * MOVSPEED;
		if (data->map[(int)data->pos_x][(int)(data->pos_y - data->dir_y * MOVSPEED)] == 0)
			data->pos_y -= data->dir_y * MOVSPEED;
	}
	if (key == XK_Left)
	{
		old_var = data->dir_x;
		data->dir_x = data->dir_x * cos(ROTSPEED) - data->dir_y * sin(ROTSPEED);
		data->dir_y = old_var * sin(ROTSPEED) + data->dir_y * cos(ROTSPEED);
		old_var = data->plane_x;
		data->plane_x = data->plane_x * cos(ROTSPEED) - data->plane_y
			* sin(ROTSPEED);
		data->plane_y = old_var * sin(ROTSPEED) + data->plane_y
			* cos(ROTSPEED);
	}
	camera2(key, data);
	return (0);
}
