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

int	get_rgba(int red, int green, int blue)
{
	return (red << 16 | green << 8 | blue );
}

int	rendering(void *ptr)
{
	t_data			*data;
	t_math			math;
	int				x;

	data = (t_data *)ptr;
	x = -1;
	//mlx_clear_window(data->mlx, data->win);
	while (++x < WIDTH)
	{
		ft_memset(&math, 0, sizeof(math));
		calculate_init(&math, data, x);
		calculate_step(&math, data);
		perform_dda(&math, data);
		calculate_draw_start_end(&math);
		draw_line(&math, data, x);
	}
	//mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}
