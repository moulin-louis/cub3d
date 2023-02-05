/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:04:38 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/05 15:00:31 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void close_prog(void *ptr)
{
	t_data *data = (t_data *)ptr;
	mlx_terminate(data->mlx);
	data->mlx = NULL;
	exit(1);
}

void init_image(t_data *data)
{
	int x;

	x = 0;
	while (x < WIDTH)
	{
		data->img[x] = mlx_new_image(data->mlx, 1, HEIGHT);
		if (!data->img[x])
			break;
		mlx_image_to_window(data->mlx, data->img[x], x, 0);
		x++;
	}
	if (x < WIDTH)
		mlx_err(data);
	return;
}

void	init_data(t_data* data)
{
	data->posX = 22;
	data->posY = 12;
	data->dirX = -1;
	data->dirY = 0;
	data->planeX = 0;
	data->planeY = 0.66;
}

void	camera(mlx_key_data_t key, void *ptr)
{
	t_data *data;

	data = (t_data*)ptr;
	if (key.key == MLX_KEY_W && (key.action == MLX_REPEAT || key.action == MLX_PRESS))
	{
		printf("pressing W detected\n");
		data->posX += data->dirX * 1.5;
		data->posY += data->dirY * 1.5;
	}
	if (key.key == MLX_KEY_S && (key.action == MLX_REPEAT || key.action == MLX_PRESS))
	{
		printf("pressing S detected\n");
		data->posX -= data->dirX * 1.5;
		data->posY -= data->dirY * 1.5;
	}
	if (key.key == MLX_KEY_D && ((key.action == MLX_REPEAT || key.action == MLX_PRESS)))
	{
		double	oldDirx = data->dirX;
		data->dirX = data->dirX * cos(-1.00001) - data->dirY * sin(-1.00001);
		data->dirY = oldDirx * sin(-1.00001) + data->dirY * cos(1);
		double oldPlanex = data->planeX;
		data->planeX = data->planeX * cos(-1.00001) - data->planeY * sin(-1.00001);
		data->planeY = oldPlanex * sin(-1.00001) + data->planeY * cos(-1.00001);
	}
	if (key.key == MLX_KEY_A && ((key.action == MLX_REPEAT || key.action == MLX_PRESS)))
	{
		double	oldDirx = data->dirX;
		data->dirX = data->dirX * cos(1) - data->dirY * sin(1);
		data->dirY = oldDirx * sin(1) + data->dirY * cos(1);
		double oldPlanex = data->planeX;
		data->planeX = data->planeX * cos(1) - data->planeY * sin(1);
		data->planeY = oldPlanex * sin(1) + data->planeY * cos(1);
	}
	return ;
}

int main(int ac, char **av)
{
	t_data data;
	if (ac != 2)
		return (ft_putstr_fd("Error\ncub3d: wrong number of arguments !\n", 2), 1);
	data = parsing(av[1]);
	mlx_close_hook(data.mlx, close_prog, (void *)&data);
	init_image(&data);
	init_data(&data);
	mlx_loop_hook(data.mlx, rendering, (void *)&data);
	mlx_key_hook(data.mlx, camera, (void*)&data);
	mlx_loop(data.mlx);
	if (data.mlx)
		mlx_terminate(data.mlx);
	return (0);
}