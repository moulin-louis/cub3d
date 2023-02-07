/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:19:27 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/07 21:04:11 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <sys/time.h>

time_t	gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_map_n_pos(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	printf("\033[2J");
	while (data->map[x])
	{
		y = 0;
		while (data->map[x][y] != END)
		{
			if (x == (int)data->pos_x && y == (int)data->pos_y)
				printf("\x1B[31mJ \x1B[37m");
			else
				printf("%d ", data->map[x][y]);
			y++;
		}
		printf("\n");
		x++;
	}
}

void	get_ms( long int old_time )
{

	long int time = gettime();
	printf("%ld ms\n", time - old_time);
	return ;
}

int	rendering(void *ptr)
{
	t_data			*data;
	t_math			math;
	int				x;

	data = (t_data *)ptr;
	x = -1;
	while (++x < WIDTH)
	{
		ft_memset(&math, 0, sizeof(math));
		calculate_init(&math, data, x);
		calculate_step(&math, data);
		perform_dda(&math, data);
		calculate_draw_start_end(&math);
		draw_line(&math, data, x);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}
