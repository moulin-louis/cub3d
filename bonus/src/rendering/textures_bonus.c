/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 11:29:21 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/16 14:05:15 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	get_pixel(t_tex tex, int x, int y)
{
	char	*pixel;
	int		result;

	pixel = tex.addr + (y * tex.size_line + x * (tex.bpp / 8));
	result = *(int *)pixel;
	return (result);
}

int	calculate_texture_coordinate(t_tex tex, t_math *math, double wall_hit)
{
	int	x;

	x = wall_hit * tex.width;
	if (math->side == 0 && math->ray_dirx > 0)
		x = tex.width - x - 1;
	if (math->side == 1 && math->ray_diry < 0)
		x = tex.width - x - 1;
	return (x);
}

void	get_tex_line(t_data *data, t_tex tex, t_math *math, t_img_data *img_d)
{
	int		tex_y;
	int		x_y[2];
	double	step;
	double	tex_pos;
	double	wall_hit;

	if (math->side == 1)
		wall_hit = data->pos_x + math->perp_wall_dist * math->ray_dirx;
	else
		wall_hit = data->pos_y + math->perp_wall_dist * math->ray_diry;
	wall_hit -= floor(wall_hit);
	x_y[0] = calculate_texture_coordinate(tex, math, wall_hit);
	step = 1.0 * tex.height / math->line_height;
	tex_pos = (math->draw_start - HEIGHT / 2 + math->line_height / 2) * step;
	x_y[1] = math->draw_start - 1;
	while (++x_y[1] <= (int)math->draw_end)
	{
		tex_y = (int)tex_pos;
		tex_pos += step;
		math->color = get_pixel(tex, x_y[0], tex_y);
		img_pix_put(img_d, math->current_x, x_y[1], math->color);
	}
}

void	draw_text_line(t_data *data, t_math *math, t_img_data *img_data)
{
	if (math->side == 1)
	{
		if (math->step_y == -1)
			get_tex_line(data, data->east, math, img_data);
		else
			get_tex_line(data, data->west, math, img_data);
	}
	else
	{
		if (math->step_x == -1)
			get_tex_line(data, data->south, math, img_data);
		else
			get_tex_line(data, data->nord, math, img_data);
	}
}
