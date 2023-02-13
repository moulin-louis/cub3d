/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:39:48 by mpignet           #+#    #+#             */
/*   Updated: 2023/02/13 15:50:49 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_chars(t_data *data)
{
	if (data->path_no)
		free(data->path_no);
	if (data->path_so)
		free(data->path_so);
	if (data->path_ea)
		free(data->path_ea);
	if (data->path_we)
		free(data->path_we);
	if (data->tmp_map)
		free_array((void **)data->tmp_map);
	if (data->map)
		free_array((void **)data->map);
}

void	clean_exit(t_data *data, int err)
{
	if (data)
	{
		clean_chars(data);
		if (data->nord.img)
			mlx_destroy_image(data->mlx, data->nord.img);
		if (data->south.img)
			mlx_destroy_image(data->mlx, data->south.img);
		if (data->west.img)
			mlx_destroy_image(data->mlx, data->west.img);
		if (data->east.img)
			mlx_destroy_image(data->mlx, data->east.img);
		if (data->img)
			mlx_destroy_image(data->mlx, data->img);
		if (data->win)
			mlx_destroy_window(data->mlx, data->win);
		if (data->mlx)
		{
			mlx_destroy_display(data->mlx);
			free(data->mlx);
		}
	}
	exit(err);
}

int	close_prog(void *ptr)
{
	clean_exit((t_data *)ptr, 0);
	return (0);
}

void	mlx_err(t_data *data)
{
	ft_putstr_fd("Error\n", 2);
	clean_exit(data, 1);
}

void	cub3d_err(t_data *data, char *err)
{
	ft_putstr_fd("Error\ncub3d: ", 2);
	ft_putstr_fd(err, 2);
	clean_exit(data, 1);
}
