/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 10:53:07 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/11 10:11:03 by loumouli         ###   ########.fr       */
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

// void	print_map(t_data *data)
// {
// 	t_img_data	img_data;
// 	int			x;
// 	int			y;

// 	x = -1;
// 	memset(&img_data, 0, sizeof img_data);
// 	img_data.img = data->img;
// 	img_data.raw_data = mlx_get_data_addr(img_data.img, &img_data.bpp, &img_data.size_line, &img_data.endian);
// 	while (++x < data->len_map_y)
// 	{
// 		y = -1;
// 		while (data->map[x][++y] != END)
// 		{
// 			if (x == (int)data->pos_x && y == (int)data->pos_y)
// 				img_pix_put(&img_data, y * 4, x * 4, get_rgb(0, 0, 255));
// 			else if (data->map[x][y] == 1)
// 				img_pix_put(&img_data, y * 4, x * 4, get_rgb(255, 0, 0));
// 			else
// 				img_pix_put(&img_data, y * 4, x * 4, get_rgb(0, 255, 0));

// 		}
// 		y = -1;
// 		while (data->map[x][++y] != END)
// 		{
// 			if (x == (int)data->pos_x && y == (int)data->pos_y)
// 				img_pix_put(&img_data, y * 4 + 1, x * 4 + 1, get_rgb(0, 0, 255));
// 			else if (data->map[x][y] == 1)
// 				img_pix_put(&img_data, y * 4 + 1, x * 4 + 1, get_rgb(255, 0, 0));
// 			else
// 				img_pix_put(&img_data, y * 4 + 1, x * 4 + 1, get_rgb(0, 255, 0));

// 		}
// 		y = -1;
// 		while (data->map[x][++y] != END)
// 		{
// 			if (x == (int)data->pos_x && y == (int)data->pos_y)
// 				img_pix_put(&img_data, y * 4 + 2, x * 4 + 2, get_rgb(0, 0, 255));
// 			else if (data->map[x][y] == 1)
// 				img_pix_put(&img_data, y * 4 + 2, x * 4 + 2, get_rgb(255, 0, 0));
// 			else
// 				img_pix_put(&img_data, y * 4 + 2, x * 4 + 2, get_rgb(0, 255, 0));

// 		}
// 		y = -1;
// 		while (data->map[x][++y] != END)
// 		{
// 			if (x == (int)data->pos_x && y == (int)data->pos_y)
// 				img_pix_put(&img_data, y * 4 + 3, x * 4 + 3, get_rgb(0, 0, 255));
// 			else if (data->map[x][y] == 1)
// 				img_pix_put(&img_data, y * 4 + 3, x * 4 + 3, get_rgb(255, 0, 0));
// 			else
// 				img_pix_put(&img_data, y * 4 + 3, x * 4 + 3, get_rgb(0, 255, 0));

// 		}
// 	}
// }


/*draw a minimap on the screen*/
void	draw_minimap(t_data *data)
{
	t_img_data	img_data;
	int x;
	int y;

	draw_square(data);
	y = -1;
	memset(&img_data, 0, sizeof img_data);
	img_data.img = data->img;
	img_data.raw_data = mlx_get_data_addr(img_data.img, &img_data.bpp, &img_data.size_line, &img_data.endian);
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x] != END)
		{
			if (x == (int)data->pos_y && y == (int)data->pos_x)
				img_pix_put(&img_data, x, y, get_rgb(0, 0, 255));
			else if (data->map[y][x] == 1)
				img_pix_put(&img_data, x, y, RED);
			else if (data->map[y][x] == 0)
				img_pix_put(&img_data, x, y, GREEN);
			
		}
	}
}


