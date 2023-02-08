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

time_t	gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	rendering(void *ptr)
{
	t_data			*data;
	t_math			math;
	//static	long	time;
	//long 			old_time;
	int		x;

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
	//old_time = time;
	//time = gettime();
	//printf("%ld\n", time - old_time);
	return (0);
}
