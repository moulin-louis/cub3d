/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 10:53:07 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/13 15:34:13 by loumouli         ###   ########.fr       */
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
	int	color;

	memset(&img_data, 0, sizeof img_data);
	img_data.img = data->img;
	img_data.raw_data = mlx_get_data_addr(img_data.img, &img_data.bpp,
			&img_data.size_line, &img_data.endian);
	color = 0;
	if (x == (int)data->pos_x && y == (int)data->pos_y)
		color = get_rgb(0, 0, 255);
	else if (data->map[x][y] == 1)
		color = get_rgb(255, 0, 0);
	else if (data->map[x][y] == 0)
		color = get_rgb(0, 255, 0);
	img_pix_put(&img_data, (x * 2) + offset, y * 2, color);
	img_pix_put(&img_data, (x * 2) + offset, (y * 2) + 1, color);
	img_pix_put(&img_data, (x * 2) + offset, (y * 2) + 2, color);

}

/*draw a minimap on the screen*/
void	draw_minimap(t_data *data)
{
	int			x;
	int			y;

	
	x = -1;
	if (data->len_map_x > HEIGHT || data->len_map_y > WIDTH)
		return ;
	while (++x < data->len_map_x )
	{
		y = -1;
		while (++y < data->len_map_y)
		{
			display_pixel(data, x, y, 0);
			display_pixel(data, x, y, 1);
			display_pixel(data, x, y, 2);
		}
	}
}
