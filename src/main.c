/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:04:38 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/05 15:08:17 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	{
		while (x)
		{
			mlx_delete_image(data->mlx, data->img[x]);
			x--;
		}
		mlx_err(data);
	}
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
	data->ceiling = get_rgba(0, 0, 0, 255);
	data->floor  = get_rgba(255, 255, 255, 255);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (ft_putstr_fd("Error\ncub3d: wrong number of args !\n", 2), 1);
	(void)av;
	memset(&data, 0, sizeof(t_data));
	data.mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", false);
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
