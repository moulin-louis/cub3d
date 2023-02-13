/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:46:44 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/11 10:23:03 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

float	calculate_buffer_zone_x(t_data *data)
{
	float	buff;

	if (data->dir_x < 0)
		buff = -0.2;
	else
		buff = 0.2;
	return (buff);
}

float	calculate_buffer_zone_y(t_data *data)
{
	float	buff;

	if (data->dir_y < 0)
		buff = -0.2;
	else
		buff = 0.2;
	return (buff);
}

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
