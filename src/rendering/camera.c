/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 12:54:37 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/13 12:31:41 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define ROTSPEED 0.05
#define MOVSPEED 0.05

void	camera_sides(int key, t_data *data, double old_var)
{
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
}

void	camera_strafe(int key, t_data *data)
{
	int		diff_x;
	int		diff_y;
	float	buff_x;
	float	buff_y;

	buff_x = calculate_buffer_zone_x(data);
	buff_y = calculate_buffer_zone_y(data);
	if (key == XK_a)
	{
		diff_x = (int)(data->pos_x - data->dir_y * MOVSPEED - buff_y);
		diff_y = (int)(data->pos_y + data->dir_x * MOVSPEED + buff_x);
		if (data->map[diff_x][(int)data->pos_y] == 0)
			data->pos_x -= data->dir_y * MOVSPEED;
		if (data->map[(int)data->pos_x][diff_y] == 0)
			data->pos_y += data->dir_x * MOVSPEED;
	}
	if (key == XK_d)
	{
		diff_x = (int)(data->pos_x + data->dir_y * MOVSPEED + buff_y);
		diff_y = (int)(data->pos_y - data->dir_x * MOVSPEED - buff_x);
		if (data->map[diff_x][(int)data->pos_y] == 0)
			data->pos_x += data->dir_y * MOVSPEED;
		if (data->map[(int)data->pos_x][diff_y] == 0)
			data->pos_y -= data->dir_x * MOVSPEED;
	}
}

void	camera_forw_backw(int key, t_data *data)
{
	int		diff_x;
	int		diff_y;
	float	buff_x;
	float	buff_y;

	buff_x = calculate_buffer_zone_x(data);
	buff_y = calculate_buffer_zone_y(data);
	if (key == XK_w)
	{
		diff_x = (int)(data->pos_x + data->dir_x * MOVSPEED + buff_x);
		diff_y = (int)(data->pos_y + data->dir_y * MOVSPEED + buff_y);
		if (data->map[diff_x][(int)data->pos_y] == 0)
			data->pos_x += data->dir_x * MOVSPEED;
		if (data->map[(int)data->pos_x][diff_y] == 0)
			data->pos_y += data->dir_y * MOVSPEED;
	}
	if (key == XK_s)
	{
		diff_x = (int)(data->pos_x - data->dir_x * MOVSPEED - buff_x);
		diff_y = (int)(data->pos_y - data->dir_y * MOVSPEED - buff_y);
		if (data->map[diff_x][(int)data->pos_y] == 0)
			data->pos_x -= data->dir_x * MOVSPEED;
		if (data->map[(int)data->pos_x][diff_y] == 0)
			data->pos_y -= data->dir_y * MOVSPEED;
	}
}

int	camera(int key, void *ptr)
{
	t_data	*data;
	double	old_var;

	data = (t_data *)ptr;
	old_var = 0;
	if (key == XK_Escape)
		close_prog(ptr);
	camera_forw_backw(key, data);
	camera_sides(key, data, old_var);
	camera_strafe(key, data);
	return (0);
}
