/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:21:37 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/11 15:21:44 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	grab_pixel_north(t_data *data, t_math *math)
{
	double	wall_hit;

	if (side == 0)
			wall_hit = data->pos_y + math->perp_wall_dist;
}

void	grab_pixel_south(t_data *data, t_math *math)
{

}

void	grab_pixel_west(t_data *data, t_math *math)
{

}

void	grab_pixel_est(t_data *data, t_math *math)
{

}