/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:39:48 by mpignet           #+#    #+#             */
/*   Updated: 2023/02/06 13:20:32 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_array(void **array)
{
	int	i;

	i = -1;
	if (!array)
		return ;
	while(array[++i])
		free(array[i]);
	free(array);
}

static	void	clean_exit(t_data *data, int err)
{
	//int	x;

	if (data)
	{
		if (data->nord)
			mlx_delete_image(data->mlx, data->nord);
		if (data->south)
			mlx_delete_image(data->mlx, data->south);
		if (data->west)
			mlx_delete_image(data->mlx, data->west);
		if (data->east)
			mlx_delete_image(data->mlx, data->east);
		// x = 0;
		// while (x < WIDTH)
		// {
		// 	mlx_delete_image(data->mlx, data->img[x]);
		// 	x++;
		// }
		if (data->img)
			mlx_delete_image(data->mlx, data->img);	
		//mlx_close_window(data->mlx);
		if (data->mlx)
			mlx_terminate(data->mlx);
		if (data->tmp_map)
			free_array((void **)data->tmp_map);
		if (data->map)
			free_array((void **)data->map);
		//free(data->mlx);
	}
	exit(err);
}


void	close_prog(void *ptr)
{
	clean_exit((t_data *)ptr, 0);
	exit(1);
}

void	mlx_err(t_data *data)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(strerror(mlx_errno), 2);
	clean_exit(data, mlx_errno);
}

void	cub3d_err(t_data *data, char *err)
{
	ft_putstr_fd("Error\ncub3d: ", 2);
	ft_putstr_fd(err, 2);
	clean_exit(data, 1);
}