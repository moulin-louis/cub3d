/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:01:34 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/08 13:53:41 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_init(t_math *math, t_data *data, int x)
{
	math->camera_x = 2 * x / (double)WIDTH - 1;
	math->ray_dirx = data->dir_x + data->plane_x * math->camera_x;
	math->ray_diry = data->dir_y + data->plane_y * math->camera_x;
	math->map_x = (int)data->pos_x;
	math->map_y = (int)data->pos_y;
	if (math->ray_dirx == 0)
			math->delta_dist_x = 0.0001;
	else
		math->delta_dist_x = fabs(1 / math->ray_dirx);
	if (math->ray_diry == 0)
		math->delta_dist_y = 0.0001;
	else
		math->delta_dist_y = fabs(1 / math->ray_diry);
}

void	calculate_step(t_math *math, t_data *data)
{
	if (math->ray_dirx < 0)
	{
		math->step_x = -1;
		math->side_dist_x = (data->pos_x - math->map_x)
			* math->delta_dist_x;
	}
	else
	{
		math->step_x = 1;
		math->side_dist_x = (math->map_x + 1.0 - data->pos_x)
			* math->delta_dist_x;
	}
	if (math->ray_diry < 0)
	{
		math->step_y = -1;
		math->side_dist_y = (data->pos_y - math->map_y)
			* math->delta_dist_y;
	}
	else
	{
		math->step_y = 1;
		math->side_dist_y = (math->map_y + 1.0 - data->pos_y)
			* math->delta_dist_y;
	}
}

void	perform_dda(t_math *math, t_data *data)
{
	while (math->hit == 0)
	{
		if (math->side_dist_x < math->side_dist_y)
		{
			math->side_dist_x += math->delta_dist_x;
			math->map_x += math->step_x;
			math->side = 0;
		}
		else
		{
			math->side_dist_y += math->delta_dist_y;
			math->map_y += math->step_y;
			math->side = 1;
		}
		if (data->map[math->map_x][math->map_y] == 1)
			math->hit = 1;
	}
}

void	calculate_draw_start_end(t_math *math)
{
	if (math->side == 0)
		math->perp_wall_dist = (math->side_dist_x - math->delta_dist_x);
	else
		math->perp_wall_dist = (math->side_dist_y - math->delta_dist_y);
	math->line_height = (int)(HEIGHT / math->perp_wall_dist);
	math->draw_start = -math->line_height / 2 + HEIGHT / 2;
	if (math->draw_start > HEIGHT)
		math->draw_start = 0;
	math->draw_end = math->line_height / 2 + HEIGHT / 2;
	if (math->draw_end >= HEIGHT)
		math->draw_end = HEIGHT - 1;
}

void	draw_line(t_math *math, t_data *data, int x)
{
	int	it;


	it = -1;
	if (data->dir_x < 0 && math->hit == 0)
		math->color = get_rgb(255, 0, 0 );
	printf("dir_x = %f dir_y = %f\n", data->dir_x, data->dir_y);
	while (++it < (int)math->draw_start)
		mlx_pixel_put(data->mlx, data->win, x, it, data->ceiling);
	it = math->draw_start - 1;
	while (++it < (int)math->draw_end)
		mlx_pixel_put(data->mlx, data->win, x, it, math->color);
	it = math->draw_end - 1;
	while (++it < HEIGHT)
		mlx_pixel_put(data->mlx, data->win, x, it, data->floor);
}
