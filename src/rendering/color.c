/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:46:44 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/12 11:26:18 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	img_pix_put(char *raw_data, const int val[5], int color)
{
	char	*pixel;
	int		x;
	int		y;
	int		bpp;
	int		size_line;

	x = val[3];
	y = val[4];
	bpp = val[0];
	size_line = val[1];
	pixel = raw_data + (y * size_line + x * (bpp / 8));
	*(int *)pixel = color;
}

int	get_rgb(int red, int green, int blue)
{
	return (red << 16 | green << 8 | blue);
}