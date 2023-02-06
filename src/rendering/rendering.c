/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:19:27 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/06 12:59:24 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <sys/time.h>

time_t	gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_map_n_pos(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	printf("\033[2J");
	while (data->map[x])
	{
		y = 0;
		while (data->map[x][y] != END)
		{
			if (x == (int)data->pos_x && y == (int)data->pos_y)
				printf("\x1B[31mJ \x1B[37m");
			else
				printf("%d ", data->map[x][y]);
			y++;
		}
		printf("\n");
		x++;
	}
}

void	rendering(void *ptr)
{
	t_data			*data;
	static long int	time;
	long int		old_time;

	data = (t_data *)ptr;
	data->img->enabled = false;
	//print_map_n_pos(data);
	for (int x = 0; x < WIDTH; x++)
	{
		double cameraX = 2 * x / (double)WIDTH - 1;
		double raydir_x = data->dir_x + data->plane_x * cameraX;
		double raydir_y  = data->dir_y + data->plane_y * cameraX;

		int mapX = (int)data->pos_x;
		int mapY = (int)data->pos_y;

		double sideDistX;
		double sideDistY;

		double deltaDistX;
		if (raydir_x == 0)
			deltaDistX = 0.0001;
		else
			deltaDistX = fabs(1 / raydir_x);

		double deltaDistY;
		if (raydir_y == 0)
			deltaDistY = 0.0001;
		else
	       	deltaDistY = fabs(1 / raydir_y);
		double perpWallDist;
		
		int stepX;
		int stepY;

		int hit = 0;
		int side = 0;
		if (raydir_x < 0)
		{
			stepX = -1;
			sideDistX = (data->pos_x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - data->pos_x) * deltaDistX;
		}
		if (raydir_y < 0)
		{
			stepY = -1;
			sideDistY = (data->pos_y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - data->pos_y) * deltaDistY;
		}	
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (data->map[mapX][mapY] > 0)
				hit = 1;
		}
	
		if(side == 0)
		{
			perpWallDist = (sideDistX - deltaDistX);
		}
		else
		{
			perpWallDist = (sideDistY - deltaDistY);
		}

		int lineHeight = (int)(HEIGHT / perpWallDist);

		unsigned int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if(drawStart > HEIGHT)
			drawStart = 0;

		unsigned int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if(drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;
		int color;
		switch(data->map[mapX][mapY])
		{
			case 1:  color = get_rgba(255, 0, 0, 255); break; //red
		}
		if (side == 1)
			color = color / 2;
		for (unsigned int y = 0; y < drawStart; y++)
			mlx_put_pixel(data->img, x, y, data->ceiling);
		for (unsigned int y = drawStart; y < drawEnd; y++)
			mlx_put_pixel(data->img, x, y, color);
		for (unsigned int y = drawEnd; y < HEIGHT; y++)
			mlx_put_pixel(data->img, x, y, data->floor);
		}
	old_time = time;
    time = gettime();
	(void)old_time;
	data->img->enabled = true;
	return ;
}
