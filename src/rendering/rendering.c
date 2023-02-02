/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:19:27 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/02 17:04:05 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*What i need:
- start pos
*/

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define  screenHeight 480

int worldMap[mapWidth][mapHeight]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	rendering(t_map data)
{
	double	posX; //current pos X
	double	posY; //current pos Y
	double	dirX; //direction vector in X
	double	dirY; //direction vector in Y
	double	planeX; //2d version of the camera plance in X
	double	planeY; //2d version of the camera plance in Y aka FOV (i think)

	posX = 10;
	posY = 10;
	dirX = -1;
	dirY = 0;
	planeX = 0;
	planeY = 0.66;
	(void)data;
	while (1)
	{
		for (int x = 0; x< screenWidth; x++)
		{
			double cameraX = 2 * x / (double)screenWidth;
			double rayDirX = dirX + planeX * cameraX;
			double rayDirY  = dirY + planeY * cameraX;
			int mapX = (int)posX;
			int mapY = (int)posY;
			double sideDistX;
			double sideDistY;
			double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
			double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
			double perpWallDist;
			int stepX;
			int stepY;

			int hit = 0;
			int side;
			if (rayDirX < 0)
			{
				stepX = -1;
				sideDistX = (posX - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - posX) * deltaDistX;
			}
			if (rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (posY - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - posY) * deltaDistY;
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
				if (worldMap[mapX][mapY] > 0) hit = 1;
			}
			if(side == 0)
				perpWallDist = (sideDistX - deltaDistX);
    		else
				perpWallDist = (sideDistY - deltaDistY);
			//printf("perpWallDist = %f\n", perpWallDist);
			int lineHeight = (int)(screenHeight / perpWallDist);
			
			int drawStart = -lineHeight / 2 + screenHeight / 2;
			if(drawStart < 0)
				drawStart = 0;
			//printf("line height = %d\n", lineHeight);
			int drawEnd = lineHeight / 2 + screenHeight / 2;
			if(drawEnd >= screenHeight)
				drawEnd = screenHeight - 1;
			int color;
			srand( time( NULL ) );
			int input_rand = rand() % 5;
			switch(input_rand)
			{
				case 1:  color = get_rgba(255, 0, 0);  break; //red
				case 2:  color = get_rgba(0, 255, 0);  break; //green
				case 3:  color = get_rgba(0, 0, 255);   break; //blue
				case 4:  color = get_rgba(0, 0, 0);  break; //white
			}
			if (side == 1) {color = color / 2;}
			mlx_image_t* img = mlx_new_image(data.mlx, 1, screenHeight);
			memset(img->pixels, 0, drawStart);
			printf("start = %d end = %d\n", drawStart, drawEnd);
			memset(img->pixels + drawStart, 255, drawEnd - drawStart);
			//memset(img->pixels + drawStart + (drawEnd - drawStart), 0, sizeof(img->pixels) - drawEnd);
			mlx_image_to_window(data.mlx, img, x, 0);
			//printf("printing a line in %d pos\n", x);
		}
	}
	return ;
}