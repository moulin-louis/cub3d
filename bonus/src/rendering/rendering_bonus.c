/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:19:27 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/13 15:25:07 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	call_mlx_fn(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

// void	print_map_n_pos(t_data *data)
// {
// 	int x;
// 	int y;

// 	x = -1;
// 	printf("\033[2J");
// 	while (data->map[++x])
// 	{
// 		y = -1;
// 		while (data->map[x][++y] != END)
// 		{
// 			if (x == (int) data->pos_x && y == (int) data->pos_y)
// 				printf("\x1B[31mJ \x1B[37m");
// 			else
// 				printf("%d ", data->map[x][y]);
// 		}
// 		printf("\n");
// 	}
// }

int	rendering(void *data)
{
	t_math		math;
	int			x;

	x = -1;
	while (++x < WIDTH)
	{
		ft_memset(&math, 0, sizeof(math));
		calculate_init(&math, (t_data *)data, x);
		calculate_step(&math, (t_data *)data);
		perform_dda(&math, (t_data *)data);
		calculate_draw_start_end(&math);
		draw_line(&math, (t_data *)data, x);
	}
	draw_minimap(data);
	call_mlx_fn((t_data *)data);
	return (0);
}
