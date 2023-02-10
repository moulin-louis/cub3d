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

/*Use to draw the area for the map*/

void	draw_square(t_data *data)
{
	t_img_data	img_data;
	int			x;
	int 		y;

	x = -1;
	memset(&img_data, 0, sizeof img_data);
	img_data.img = data->img;
	img_data.raw_data = mlx_get_data_addr(img_data.img, &img_data.bpp, &img_data.size_line, &img_data.endian);
	while (++x < data->len_map_y * 10)
	{
		y = -1;
		while (++y < data->len_map_x * 10)
			img_pix_put(&img_data, x, y, BLACK);
	}
}


/*draw a minimap on the screen*/
void	draw_minimap(t_data *data)
{
	t_img_data	img_data;
	int x;
	int y;

	draw_square(data);
	x = -1;
	memset(&img_data, 0, sizeof img_data);
	img_data.img = data->img;
	img_data.raw_data = mlx_get_data_addr(img_data.img, &img_data.bpp, &img_data.size_line, &img_data.endian);
	img_pix_put(&img_data, 0, 10, get_rgb(0, 0, 255));
	while (++x < data->len_map_y)
	{
		y = -1;
		while (++y < data->len_map_x)
		{
			if (data->map[y][x] == 1)
				img_pix_put(&img_data, x, y + 10, RED);
			else
				img_pix_put(&img_data, x, y + 10	, GREEN);
		}
	}
}