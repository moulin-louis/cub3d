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

void	call_mlx_fn(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

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
	return (call_mlx_fn((t_data *)data), 0);
}
