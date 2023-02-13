/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:04:38 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/13 15:21:13 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	ft_strlen_custom(const int *line)
{
	int	result;

	result = 0;
	while (line[result] != END)
			result++;
	return (result);
}

void	set_len_map(t_data *data)
{
	int	it;

	while (data->map[data->len_map_x])
		data->len_map_x++;
	it = 0;
	while (data->map[it])
	{
		if (ft_strlen_custom(data->map[it]) > data->len_map_y)
				data->len_map_y = ft_strlen_custom(data->map[it]);
		else
			it++;
	}
}

void	setup_hook(t_data *data)
{
	mlx_hook(data->win, ButtonPress, ButtonPressMask, &camera_mouse, data);
	mlx_hook(data->win, ButtonRelease, ButtonReleaseMask, &camera_mouse, data);
	mlx_hook(data->win, KeyPress, KeyPressMask, &camera, data);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, &camera, data);
	mlx_hook(data->win, ClientMessage, NoEventMask, &close_prog, data);
	mlx_loop_hook(data->mlx, rendering, data);
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
	setup_hook(&data);
	mlx_loop(data.mlx);
	return (0);
}
