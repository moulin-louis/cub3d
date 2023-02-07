/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:04:38 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/07 20:49:14 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	init_image(t_data *data)
// {
// 	int	x;

// 	x = 0;
// 	while (x < WIDTH)
// 	{
// 		data->img[x] = mlx_new_image(data->mlx, 1, HEIGHT);
// 		memset(data->img[x]->pixels, 255, data->img[x]->width * data->img[x]->height * sizeof(int32_t));
// 		if (!data->img[x])
// 			break ;
// 		mlx_image_to_window(data->mlx, data->img[x], x, 0);
// 		x++;
// 	}
// 	if (x < WIDTH)
// 	{
// 		while (x)
// 		{
// 			mlx_delete_image(data->mlx, data->img[x]);
// 			x--;
// 		}
// 		mlx_err(data);
// 	}
// 	return ;
// }

void	init_data(t_data *data)
{
	data->pos_x = 11.5;
	data->pos_y = 25.5;
	data->dir_x = -1;
	data->dir_y = 0;
	data->plane_x = 0;
	data->plane_y = 0.66;
	data->ceiling = get_rgba(0, 0, 0, 255);
	data->floor = get_rgba(255, 255, 255, 255);
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
