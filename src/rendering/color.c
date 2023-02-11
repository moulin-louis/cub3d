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

void	img_pix_put(t_img_data *img_data, int x, int y, int color)
{
	char	*pixel;

	pixel = img_data->raw_data + (y * img_data->size_line
								  + x * (img_data->bpp / 8));
	*(int *)pixel = color;
}

int	get_rgb(int red, int green, int blue)
{
	return (red << 16 | green << 8 | blue);
}

void	hit_in_y(t_data *data, t_math *math)
{
	(void)data;
	grab_pixel_west(data, math);
	if (math->step_y == -1)
		grab_pixel_est(data, math);
}

void	hit_in_x(t_data *data, t_math *math)
{
	(void)data;
	grab_pixel_north(data, math);
	if (math->step_x == -1)
		grab_pixel_south(data, math);
}

void	check_side(t_data *data, t_math *math)
{
	if (math->side == 1)
		hit_in_y(data, math);
	else
		hit_in_x(data, math);
}
