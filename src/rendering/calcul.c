/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:01:34 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/10 15:16:55 by mpignet          ###   ########.fr       */
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
			math->delta_dist_x = 1e30;
	else
		math->delta_dist_x = fabs(1 / math->ray_dirx);
	if (math->ray_diry == 0)
		math->delta_dist_y = 1e30;
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

int	get_pixel(t_tex tex, int x, int y)
{
	char	*pixel;
	int		result;

	pixel = tex.addr + (y * tex.size_line + x * (tex.bpp / 8));
	result = *(int *)pixel;
	return (result);
}

void	get_tex_line(t_data *data, t_tex tex, t_math *math, int *val, t_img *img)
{
	int		tex_y;
	int		x;
	double	step;
	double	tex_pos;
	double	wall_hit;

	wall_hit = data->pos_y + math->perp_wall_dist * math->ray_diry;
	wall_hit -= floor(wall_hit);
	x = wall_hit * data->west.width;
	// if ((math->side == 1 && math->ray_diry < 0)
	// 	|| (math->side == 0 && math->ray_dirx > 0))
	// 	x = tex.width - x - 1;
	step = 1.0 * tex.height / math->line_height;
	tex_pos = (math->draw_start - HEIGHT / 2 + math->line_height / 2) * step;
	while (++val[4] < (int)math->draw_end)
	{
		tex_y = (int)tex_pos;
		tex_pos += step;
		math->color = get_pixel(tex, x, tex_y);
		img_pix_put(img->data, val, math->color);
	}
}

void	draw_line(t_math *math, t_data *data, int x)
{
	t_img	*img;
	int		val[5];

	val[4] = -1;
	img = (t_img *)data->img;
	mlx_get_data_addr(data->img, &val[0], &val[1], &val[2]);
	val[3] = x;
	while (++val[4] < (int)math->draw_start)
		img_pix_put(img->data, val, data->ceiling);
	val[4] = math->draw_start - 1;
	if (math->side == 1)
	{
		if (math->step_y == -1)
			get_tex_line(data, data->east, math, val, img);
		else
			get_tex_line(data, data->west, math, val, img);
	}
	else
	{
		if (math->step_x == -1)
			get_tex_line(data, data->nord, math, val, img);
		else
			get_tex_line(data, data->south, math, val, img);
	}
	val[4] = math->draw_end - 1;
	while (++val[4] < HEIGHT + 1)
		img_pix_put(img->data, val, data->floor);
}
