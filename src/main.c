/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:04:38 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/03 18:36:37 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void close_prog(void *ptr)
{
	t_data	*data = (t_data *)ptr;
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

int	main(int ac, char **av)
{
	t_data data;
	if (ac != 2)
		return (ft_putstr_fd("Error\ncub3d: wrong number of arguments !\n", 2), 1);
	data = parsing(av[1]);
	mlx_close_hook(data.mlx, close_prog, (void *)&data);
	init_image(&data);
	mlx_loop_hook(data.mlx, rendering, (void *)&data);
	mlx_loop(data.mlx);
	if (data.mlx)
		mlx_terminate(data.mlx);
	return (0);
}