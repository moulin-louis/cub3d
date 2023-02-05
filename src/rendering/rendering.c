/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:19:27 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/05 15:45:21 by loumouli         ###   ########.fr       */
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

// void	print_map_n_pos(t_data *data)
// {
// 	int	x;
// 	int	y;

// 	x = 0;
// 	y = 0;
// 	printf("\033[2J");
// 	while (data->map[x])
// 	{
// 		y = 0;
// 		while (y != END)
// 		{
// 			if (x == (int)data->pos_x && y == (int)data->pos_y)
// 				printf("\x1B[31mJ \x1B[37m");
// 			else
// 				printf("%d ", data->map[x][y]);
// 			y++;
// 		}
// 		printf("\n");
// 		x++;
// 	}
// }



void	rendering(void *ptr)
{
	t_data* 		data;
	static long int time;
  	long int 		oldTime;
	
	data = (t_data *)ptr;
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

		double deltaDistX = fabs(1 / raydir_x);
		double deltaDistY = fabs(1 / raydir_y);

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
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
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
			//Check if ray has hit a wall
			if (data->map[mapX][mapY] > 0)
				hit = 1;
		}
		if(side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);

		int lineHeight = (int)(HEIGHT / perpWallDist);

		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if(drawStart < 0)
			drawStart = 0;

		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if(drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;
			
		int color;
		switch(data->map[mapX][mapY])
		{
			case 1:  color = get_rgba(255, 0, 0, 255); break; //red
			case 2:  color = get_rgba(0, 255, 0, 255); break; //green
			case 3:  color = get_rgba(0, 0, 255, 255); break; //blue
			case 4:  color = get_rgba(255, 255, 255, 255); break; //white
			default: color = get_rgba(0, 0, 0, 255);
		}
		if (side == 1)
			color = color / 2;
		
		//printf("nbr pixel to draw = %d\n", drawEnd - drawStart);
		for (unsigned long it = 0; it < drawStart * sizeof(int32_t);)
		{
			data->img[x]->pixels[it] = (uint8_t)255;//et_r(data->ceiling);
			it++;
			data->img[x]->pixels[it] = (uint8_t)255;//get_g(data->ceiling);
			it++;
			data->img[x]->pixels[it] = (uint8_t)255;//get_b(data->ceiling);
			it++;
			data->img[x]->pixels[it] = (uint8_t)255;//get_a(data->ceiling);
			it++;
		}
		for (unsigned long it = drawStart; it < drawStart * sizeof(int32_t); )
		{
			data->img[x]->pixels[it] = (uint8_t)get_r(color);
			it++;
			data->img[x]->pixels[it] = (uint8_t)get_g(color);
			it++;
			data->img[x]->pixels[it] = (uint8_t)get_b(color);
			it++;
			data->img[x]->pixels[it] = (uint8_t)get_a(color);
			it++;
		}
		for (unsigned long it = drawEnd; it < (HEIGHT - drawEnd) * sizeof(int32_t); )
		{
			data->img[x]->pixels[it] = (uint8_t)0;//get_r(data->floor);
			it++;
			data->img[x]->pixels[it] = (uint8_t)0;//get_g(data->floor);
			it++;
			data->img[x]->pixels[it] = (uint8_t)0;//get_b(data->floor);
			it++;
			data->img[x]->pixels[it] = (uint8_t)0;//get_a(data->floor);
			it++;
		}
	}
	oldTime = time;
    time = gettime();
	//dprintf(2, "old time = %ld time = %ld\n", oldTime, time);
	//dprintf(2, "%ld ms since last frame\n", time - oldTime);
	(void)oldTime;
	return ;
}
