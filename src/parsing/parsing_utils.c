/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:56:27 by mpignet           #+#    #+#             */
/*   Updated: 2023/02/03 16:09:11 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	clean_exit(t_data *data, int err)
{
	int	i;

	i = -1;
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
		if (data->mlx)
		mlx_terminate(data->mlx);
		if (data->map)
		{		
			while(data->map[++i])
				free(data->map[i]);
			free(data->map);
		}
		free(data);
	}
	exit(err);
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

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;
	int	ls1;
	int	ls2;

	if (!s1 || !s2)
		return (1);
	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	if (ls1 != ls2)
		return (1);
	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}