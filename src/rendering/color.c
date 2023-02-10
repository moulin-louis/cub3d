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

void	img_pix_put(char *raw_data, const int val[3], int color)
{
	char	*pixel;

	pixel = raw_data + (val[4] * val[1] + val[3] * (val[0] / 8));
	*(int *)pixel = color;
}

int	get_rgb(int red, int green, int blue)
{
	return (red << 16 | green << 8 | blue);
}

void	hit_in_y(t_data *data, t_math *math)
{
	double	wall_hit;
	int		tex_point;

	wall_hit = data->pos_x + math->perp_wall_dist * math->ray_dirx;
	wall_hit -= floor(wall_hit);
	if (math->step_y != -1)
		tex_point = wall_hit * data->west.width;
	if (math->step_y == -1)
		tex_point = wall_hit * data->east.width;
	math->color = tex_point;
	// math->color = get_rgb(0, 0, 255);
	// if (math->step_y == -1)
	// 		math->color /= 2;
}

void	hit_in_x(t_data *data, t_math *math)
{
	double	wall_hit;
	int		tex_point;

	wall_hit = data->pos_y + math->perp_wall_dist * math->ray_diry;
	wall_hit -= floor(wall_hit);
	if (math->step_x != -1)	
		tex_point = wall_hit * data->south.width;
	if (math->step_x == -1)
		tex_point = wall_hit * data->nord.width;
	math->color = tex_point;
	// math->color = get_rgb(255, 0, 0);
	// if (math->step_y == -1)
	// 		math->color /= 2;
}

void	check_side(t_data *data, t_math *math)
{
	if (math->side == 1)
		hit_in_y(data, math);
	else
		hit_in_x(data, math);
}
