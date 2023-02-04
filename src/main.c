/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:04:38 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/04 11:03:34 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	close_prog(void *ptr)
{
	t_data	*data;

	data = (t_data *)ptr;
	mlx_terminate(data->mlx);
	data->mlx = NULL;
	exit(1);
}

void	init_image(t_data *data)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		data->img[x] = mlx_new_image(data->mlx, 1, HEIGHT);
		if (!data->img[x])
			break ;
		mlx_image_to_window(data->mlx, data->img[x], x, 0);
		x++;
	}
	if (x < WIDTH)
		mlx_err(data);
	return ;
}

void	init_data(t_data *data)
{
	data->pos_x = 22;
	data->pos_y = 12;
	data->dir_x = -1;
	data->dir_y = 0;
	data->plane_x = 0;
	data->plane_y = 0.66;
}

void	camera(mlx_key_data_t key, void *ptr)
{
	t_data	*data;
	double	old_dir_x;
	double	old_plane_x;

	data = (t_data *)ptr;
	if (key.key == MLX_KEY_W && (key.action == MLX_REPEAT
			|| key.action == MLX_PRESS))
	{
		data->pos_x += data->dir_x * 1.5;
		data->pos_y += data->dir_y * 1.5;
	}
	if (key.key == MLX_KEY_S && (key.action == MLX_REPEAT
			|| key.action == MLX_PRESS))
	{
		data->pos_x -= data->dir_x * 1.5;
		data->pos_y -= data->dir_y * 1.5;
	}
	if (key.key == MLX_KEY_D && ((key.action == MLX_REPEAT
				|| key.action == MLX_PRESS)))
	{
		old_dir_x = data->dir_x;
		data->dir_x = data->dir_x * cos(-1.001) - data->dir_y * sin(-1.001);
		data->dir_y = old_dir_x * sin(-1.001) + data->dir_y * cos(1);
		old_plane_x = data->plane_x;
		data->plane_x = data->plane_x * cos(-1.001) - data->plane_y * sin(-1.001);
		data->plane_y = old_plane_x * sin(-1.001) + data->plane_y * cos(-1.001);
	}
	if (key.key == MLX_KEY_A && ((key.action == MLX_REPEAT
				|| key.action == MLX_PRESS)))
	{
		old_dir_x = data->dir_x;
		data->dir_x = data->dir_x * cos(1) - data->dir_y * sin(1);
		data->dir_y = old_dir_x * sin(1) + data->dir_y * cos(1);
		old_plane_x = data->plane_x;
		data->plane_x = data->plane_x * cos(1) - data->plane_y * sin(1);
		data->plane_y = old_plane_x * sin(1) + data->plane_y * cos(1);
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (ft_putstr_fd("Error\ncub3d: wrong number of args !\n", 2), 1);
	data = parsing(av[1]);
	mlx_close_hook(data.mlx, close_prog, (void *)&data);
	init_image(&data);
	init_data(&data);
	mlx_loop_hook(data.mlx, rendering, (void *)&data);
	mlx_key_hook(data.mlx, camera, (void *)&data);
	mlx_loop(data.mlx);
	if (data.mlx)
		mlx_terminate(data.mlx);
	return (0);
}
