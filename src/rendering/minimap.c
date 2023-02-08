/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:17:35 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/08 18:17:35 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_index(int *arr, t_data *data, int x)
{
	int y;

	y = -1;
	while (arr[++y] != END)
	{
		if (arr[y] == 1)
			mlx_pixel_put(data->mlx, data->win, x, y, get_rgb(255, 0, 0));
		else
			mlx_pixel_put(data->mlx, data->win, x, y, get_rgb(0, 255, 0));
	}
	y = -1;
	while (arr[++y] != END)
	{
		if (arr[y] == 1)
			mlx_pixel_put(data->mlx, data->win, x + 1, y, get_rgb(255, 0, 0));
		else
			mlx_pixel_put(data->mlx, data->win, x + 1, y, get_rgb(0, 255, 0));
	}
	y = -1;
	while (arr[++y] != END)
	{
		if (arr[y] == 1)
			mlx_pixel_put(data->mlx, data->win, x + 2, y, get_rgb(255, 0, 0));
		else
			mlx_pixel_put(data->mlx, data->win, x + 2, y, get_rgb(0, 255, 0));
	}
	y = -1;
	while (arr[++y] != END)
	{
		if (arr[y] == 1)
			mlx_pixel_put(data->mlx, data->win, x + 3, y, get_rgb(255, 0, 0));
		else
			mlx_pixel_put(data->mlx, data->win, x + 3, y, get_rgb(0, 255, 0));
	}
	y = -1;
	while (arr[++y] != END)
	{
		if (arr[y] == 1)
			mlx_pixel_put(data->mlx, data->win, x + 3, y, get_rgb(255, 0, 0));
		else
			mlx_pixel_put(data->mlx, data->win, x + 3, y, get_rgb(0, 255, 0));
	}
}

void	draw_minimap(t_data *data)
{
	int	x;

	x = -1;
	printf("draw minimap\n");
	while (data->map[++x])
	{
		draw_index(data->map[x], data, x);
		draw_index(data->map[x], data, x + 1);
		draw_index(data->map[x], data, x + 2);
		draw_index(data->map[x], data, x + 3);
		draw_index(data->map[x], data, x + 4);
		draw_index(data->map[x], data, x + 5);
		draw_index(data->map[x], data, x + 6);
		draw_index(data->map[x], data, x + 7);
		draw_index(data->map[x], data, x + 8);
	}
}