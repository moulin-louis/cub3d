/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 10:53:07 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/10 10:53:07 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_square(t_data *data)
{
	int	val[5];

	val[3] = -1;
	mlx_get_data_addr(data->img, &val[0], &val[1], &val[2]);
	while (++val[3] < data->len_map_x * 4)
	{
		val[4] = -1;
		while (++val[4] < data->len_map_y * 4)
			img_pix_put(((t_img *)(data->img))->data, val, BLACK);
	}
}

void	draw_this_line(t_data *data, int x, int val[5])
{
	int	y;
	int	offset;

	offset = 0;
	while (offset < 40)
	{
		y = -1;
		val[3] = x + offset;
		while (data->map[x][++y] != END)
		{
			val[4] = y;
			if (data->map[x][y] == 1)
				img_pix_put(((t_img *)(data->img))->data, val, RED);
			else if (data->map[x][y] == 0)
				img_pix_put(((t_img *)(data->img))->data, val, GREEN);
		}
		offset++;
	}
}

void	draw_minimap(t_data *data)
{
	int	x;
	int	val[5];

	draw_square(data);
	mlx_get_data_addr(data->img, &val[0], &val[1], &val[2]);
	x = -1;
	while (data->map[++x])
		draw_this_line(data, x, val);
}
