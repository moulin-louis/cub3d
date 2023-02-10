/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:04:38 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/08 16:45:58 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	set_len_map(t_data *data)
{
	int x;
	int y;

	x = 0;
	while (data->map[x])
		x++;
	data->len_map_y = x;
	y = 0;
	while (data->map[0][y] != END)
			y++;
	data->len_map_x = y;
}

int	main(int ac, char **av)
{
	t_data	data;

	if (WIDTH > 1920 || HEIGHT > 1080)
			return (printf("window is too big\n"), 1);
	if (WIDTH / 16 != HEIGHT / 9 || (WIDTH % 16 != HEIGHT % 9))
			return (printf("Wrong ratio for the window\n"), 1);
	if (ac != 2)
		return (ft_putstr_fd("Error\ncub3d: wrong number of args !\n", 2), 1);
	data = parsing(av[1]);
	set_len_map(&data);
	mlx_hook(data.win, KeyPress, KeyPressMask, &camera, &data);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, &camera, &data);
	mlx_hook(data.win, ClientMessage, NoEventMask, &close_prog, &data);
	mlx_loop_hook(data.mlx, rendering, &data);
	mlx_loop(data.mlx);
	return (0);
}
