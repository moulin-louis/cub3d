/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:03:51 by mpignet           #+#    #+#             */
/*   Updated: 2023/02/06 15:50:52 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_color(t_data *data, char **tmp)
{
	int		color;
	char	**buff;

	buff = ft_split(tmp[1], ',');
	if (!buff)
		cub3d_err(data, "Malloc error\n");
	else if (array_len((void **)buff) != 3)
	{
		free_array((void **)tmp);
		free_array((void **)buff);
		cub3d_err(data, "Color description error : format needed: r, g, b\n");
	}
	color = get_rgb(ft_atoi(buff[0]), ft_atoi(buff[1]), ft_atoi(buff[2]));
	return (free_array((void **)buff), color);
}

static void	check_and_add_texture(t_data *data, char **tmp)
{
	if (!ft_strcmp(tmp[0], "NO"))
	{
		if (data->nord)
			cub3d_err(data, "Mutiple path definitions for North walls\n");
		data->nord = mlx_xpm_file_to_image(data->mlx, tmp[1], NULL, NULL);
	}
	else if (!ft_strcmp(tmp[0], "SO"))
	{
		if (data->south)
			cub3d_err(data, "Mutiple path definitions for South walls\n");
		data->south = mlx_xpm_file_to_image(data->mlx, tmp[1], NULL, NULL);
	}
	else if (!ft_strcmp(tmp[0], "WE"))
	{
		if (data->west)
			cub3d_err(data, "Mutiple path definitions for West walls\n");
		data->west = mlx_xpm_file_to_image(data->mlx, tmp[1], NULL, NULL);
	}
	else if (!ft_strcmp(tmp[0], "EA"))
	{
		if (data->east)
			cub3d_err(data, "Mutiple path definitions for East walls\n");
		data->east = mlx_xpm_file_to_image(data->mlx, tmp[1], NULL, NULL);
	}
}

void	check_texture_color_error(t_data *data)
{
	if (!data->nord)
		cub3d_err(data, "Missing path for North walls\n");
	if (!data->south)
		cub3d_err(data, "Missing path for South walls\n");
	if (!data->west)
		cub3d_err(data, "Missing path for West walls\n");
	if (!data->east)
		cub3d_err(data, "Missing path for East walls\n");
	if (!data->floor)
		cub3d_err(data, "Missing color for Floor\n");
	if (!data->ceiling)
		cub3d_err(data, "Missing color for Ceiling\n");
}

void	add_textures(t_data *data)
{
	int		i;
	char	**tmp;

	i = -1;
	while (data->tmp_map[++i])
	{
		if (data->tmp_map[i] == NULL)
			continue ;
		tmp = ft_split(data->tmp_map[i], ' ');
		if (!tmp)
			cub3d_err(data, "Malloc error\n");
		check_and_add_texture(data, tmp);
		if (!ft_strcmp(tmp[0], "F"))
		{
			if (data->floor)
				cub3d_err(data, "Mutiple color definitions for Floor\n");
			data->floor = get_color(data, tmp);
		}
		else if (!ft_strcmp(tmp[0], "C"))
		{
			if (data->ceiling)
				cub3d_err(data, "Mutiple color definitions for Ceiling\n");
			data->ceiling = get_color(data, tmp);
		}
		free_array((void **)tmp);
	}
}
