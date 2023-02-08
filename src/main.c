/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:04:38 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/08 14:31:02 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_data *data)
{
	data->pos_x = 11.5;
	data->pos_y = 25.5;
	data->dir_x = -1;
	data->dir_y = 0;
	data->plane_x = 0;
	data->plane_y = FOV;
	data->ceiling = get_rgb(0, 0, 0);
	data->floor = get_rgb(255, 255, 255);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (ft_putstr_fd("Error\ncub3d: wrong number of args !\n", 2), 1);
	data = parsing(av[1]);
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	init_data(&data);
	mlx_hook(data.win, KeyPress, KeyPressMask, &camera, &data);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, &camera, &data);
	mlx_hook(data.win, ClientMessage, NoEventMask, &close_prog, &data);
	mlx_loop_hook(data.mlx, rendering, &data);
	mlx_loop(data.mlx);
	return (0);
}
