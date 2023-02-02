/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:04:38 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/02 16:43:16 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void close_prog(void *ptr)
{
	t_map* data = (t_map *)ptr;
	mlx_terminate(data->mlx);
	data->mlx = NULL;
	exit(1);
}

int	main(int ac, char **av)
{
	t_map	data;
	if (ac != 2)
		return (ft_putstr_fd("cub3d: wrong number of arguments !\n", 2), 1);
	//data = parsing(av[1]);
	(void)av;
	memset(&data, 0, sizeof(data));
	data.mlx = mlx_init(640, 480, "cub3d", false);
	rendering(data);
	mlx_close_hook(data.mlx, close_prog, (void *)&data);
	mlx_loop(data.mlx);
	if (data.mlx)
		mlx_terminate(data.mlx);
	return (0);
}