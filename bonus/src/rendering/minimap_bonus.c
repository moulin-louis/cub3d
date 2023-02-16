/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 10:53:07 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/16 13:38:30 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/*Use to draw the area for the map*/

void	draw_square(t_data *data)
{
	t_img_data	img_data;
	int			x;
	int			y;

	x = -1;
	memset(&img_data, 0, sizeof img_data);
	img_data.img = data->img;
	img_data.raw_data = mlx_get_data_addr(img_data.img, &img_data.bpp,
			&img_data.size_line, &img_data.endian);
	while (++x < data->len_map_y * 4)
	{
		y = -1;
		while (++y < data->len_map_x * 4)
			img_pix_put(&img_data, x, y, get_rgb(0, 0, 0));
	}
}

void	display_pixel(t_data *data, int x, int y, int offset)
{
	t_img_data	img_data;
	int			color;

	memset(&img_data, 0, sizeof img_data);
	img_data.img = data->img;
	img_data.raw_data = mlx_get_data_addr(img_data.img, &img_data.bpp,
			&img_data.size_line, &img_data.endian);
	color = 0;
	if (y == (int)data->pos_x && x == (int)data->pos_y)
		color = get_rgb(0, 0, 255);
	else if (data->map[y][x] == 1)
		color = get_rgb(128, 56, 0);
	else if (data->map[y][x] == 0)
		color = get_rgb(128, 128, 128);
	img_pix_put(&img_data, (x * 6) + offset, (y * 6) + 0, color);
	img_pix_put(&img_data, (x * 6) + offset, (y * 6) + 1, color);
	img_pix_put(&img_data, (x * 6) + offset, (y * 6) + 2, color);
	img_pix_put(&img_data, (x * 6) + offset, (y * 6) + 3, color);
	img_pix_put(&img_data, (x * 6) + offset, (y * 6) + 4, color);
	img_pix_put(&img_data, (x * 6) + offset, (y * 6) + 5, color);
}

/*draw a minimap on the screen*/
void	draw_minimap(t_data *data)
{
	int			x;
	int			y;

	if (data->len_map_x > HEIGHT || data->len_map_y > WIDTH)
		return ;
	y = -1;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x] != END)
		{
			display_pixel(data, x, y, 0);
			display_pixel(data, x, y, 1);
			display_pixel(data, x, y, 2);
			display_pixel(data, x, y, 3);
			display_pixel(data, x, y, 4);
			display_pixel(data, x, y, 5);
		}
	}
}
