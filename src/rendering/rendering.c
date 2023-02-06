/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:19:27 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/06 14:33:04 by loumouli         ###   ########.fr       */
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

void	rendering(void *ptr)
{
	t_data			*data;
	t_math			math;
	int				x;
	static long int	time;
	long int		old_time;

	data = (t_data *)ptr;
	ft_memset(&math, 0, sizeof(math));
	data->img->enabled = false;
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
	old_time = time;
	time = gettime();
	printf("%ld fps\n", 1000/(time - old_time));
	data->img->enabled = true;
	return ;
}
