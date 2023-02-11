/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:46:44 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/10 14:59:41 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	img_pix_put(char *raw_data, const int val[5], int color)
{
	char	*pixel;
	int		x;
	int		y;
	int		bpp;
	int		size_line;

	x = val[3];
	y = val[4];
	bpp = val[0];
	size_line = val[1];
	pixel = raw_data + (y * size_line + x * (bpp / 8));
	*(int *)pixel = color;
}

int	get_rgb(int red, int green, int blue)
{
	return (red << 16 | green << 8 | blue);
}

/* int	hit_in_y(t_data *data, t_math *math)
{
	double	wall_hit;

	wall_hit = data->pos_x + math->perp_wall_dist * math->ray_dirx;
	wall_hit -= floor(wall_hit);
	if (math->step_y != -1)
	{
		data->west.hit_x = wall_hit * data->west.width;
		if (math->ray_diry < 0)
			data->west.hit_x = data->west.width - data->west.hit_x - 1;
		return (3);
	}
	if (math->step_y == -1)
	{
		data->east.hit_x = wall_hit * data->east.width;
		if (math->ray_diry < 0)
			data->east.hit_x = data->east.width - data->east.hit_x - 1;
		return (4);
	}
	// math->color = get_rgb(0, 0, 255);
	// if (math->step_y == -1)
	// 		math->color /= 2;
	return (0);
}

int	hit_in_x(t_data *data, t_math *math)
{
	double	wall_hit;

	wall_hit = data->pos_y + math->perp_wall_dist * math->ray_diry;
	wall_hit -= floor(wall_hit);
	if (math->step_x != -1)
	{
		data->south.hit_x = wall_hit * data->south.width;
		if (math->ray_dirx > 0)
			data->south.hit_x = data->south.width - data->south.hit_x - 1;
		return (1);
	}
	if (math->step_x == -1)
	{
		data->nord.hit_x = wall_hit * data->nord.width;
		if (math->ray_dirx > 0)
			data->nord.hit_x = data->nord.width - data->nord.hit_x - 1;
		return (2);
	}
	// math->color = get_rgb(255, 0, 0);
	// if (math->step_y == -1)
	// 		math->color /= 2;
	return (0);
} */

/* int	check_side(t_data *data, t_math *math)
{
	if (math->side == 1)
		return (hit_in_y(data, math));
	else
		return (hit_in_x(data, math));
}
 */