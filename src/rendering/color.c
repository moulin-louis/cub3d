/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:46:44 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/08 15:04:31 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_rgb(int red, int green, int blue)
{
	return (red << 16 | green << 8 | blue);
}

int	check_side(t_data *data)
{
	int result;

	(void)data;
	//printf("data->dir_x = %f data->dir_y = %f\n", data->dir_x, data->dir_y);
	result = 0;
	return (result);
}