/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 12:54:37 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/05 15:59:10 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	camera2(mlx_key_data_t key, t_data *data)
{

	if (key.key == MLX_KEY_D && ((key.action == MLX_REPEAT
				|| key.action == MLX_PRESS)))
	{
		data->pos_y += 1;
	}
	if (key.key == MLX_KEY_A && ((key.action == MLX_REPEAT
				|| key.action == MLX_PRESS)))
	{
		data->pos_y -= 1;
	}
}

void	camera(mlx_key_data_t key, void *ptr)
{
	t_data	*data;

	data = (t_data *)ptr;
	if (key.key == MLX_KEY_W && (key.action == MLX_REPEAT
			|| key.action == MLX_PRESS))
	{
		data->pos_x -= 1;
	}
	if (key.key == MLX_KEY_S && (key.action == MLX_REPEAT
			|| key.action == MLX_PRESS))
	{
		data->pos_x += 1;
	}
	camera2(key, data);
}
