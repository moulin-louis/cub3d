/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:03:51 by mpignet           #+#    #+#             */
/*   Updated: 2023/02/08 17:06:54 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	get_color(t_data *data, char **tmp)
{
	int		color;
	char	**buff;

	buff = ft_split(tmp[1], ',');
	if (!buff)
	{
		free_array((void **)tmp);
		cub3d_err(data, "Malloc error\n");
	}
	else if (array_len((void **)buff) != 3)
	{
		free_array((void **)tmp);
		free_array((void **)buff);
		cub3d_err(data, "Color description error : format needed: r, g, b\n");
	}
	color = get_rgb(ft_atoi(buff[0]), ft_atoi(buff[1]), ft_atoi(buff[2]));
	return (free_array((void **)buff), color);
}

static void	add_we_ea(t_data *data, char **tmp)
{
	if (!ft_strcmp(tmp[0], "WE"))
	{
		if (data->west.img)
			cub3d_err(data, "Mutiple path definitions for West walls\n");
		data->west.img = mlx_xpm_file_to_image(data->mlx, tmp[1],
				&data->west.width, &data->west.height);
		data->west.addr = mlx_get_data_addr(data->west.img,
				&data->west.bpp, &data->west.size_line,
				&data->west.endian);
	}
	else if (!ft_strcmp(tmp[0], "EA"))
	{
		if (data->east.img)
			cub3d_err(data, "Mutiple path definitions for East walls\n");
		data->east.img = mlx_xpm_file_to_image(data->mlx, tmp[1],
				&data->east.width, &data->east.height);
		data->east.addr = mlx_get_data_addr(data->east.img,
				&data->east.bpp, &data->east.size_line,
				&data->east.endian);
	}
}

static void	check_and_add_texture(t_data *data, char **tmp)
{
	if (!ft_strcmp(tmp[0], "NO"))
	{
		if (data->nord.img)
			cub3d_err(data, "Mutiple path definitions for North walls\n");
		data->nord.img = mlx_xpm_file_to_image(data->mlx, tmp[1],
				&data->nord.width, &data->nord.height);
		data->nord.addr = mlx_get_data_addr(data->nord.img,
				&data->nord.bpp, &data->nord.size_line,
				&data->nord.endian);
	}
	else if (!ft_strcmp(tmp[0], "SO"))
	{
		if (data->south.img)
			cub3d_err(data, "Mutiple path definitions for South walls\n");
		data->south.img = mlx_xpm_file_to_image(data->mlx, tmp[1],
				&data->south.width, &data->south.height);
		data->south.addr = mlx_get_data_addr(data->south.img,
				&data->south.bpp, &data->south.size_line,
				&data->south.endian);
	}
	add_we_ea(data, tmp);
}

void	check_texture_color_error(t_data *data)
{
	if (!data->nord.img)
		cub3d_err(data, "Missing path for North walls\n");
	if (!data->south.img)
		cub3d_err(data, "Missing path for South walls\n");
	if (!data->west.img)
		cub3d_err(data, "Missing path for West walls\n");
	if (!data->east.img)
		cub3d_err(data, "Missing path for East walls\n");
	if (data->floor == -1)
		cub3d_err(data, "Missing color for Floor\n");
	if (data->ceiling == -1)
		cub3d_err(data, "Missing color for Ceiling\n");
}

void	add_textures_and_colors(t_data *data)
{
	int		i;
	char	**tmp;

	i = -1;
	while (data->tmp_map[++i])
	{
		tmp = ft_split(data->tmp_map[i], ' ');
		if (!tmp)
			cub3d_err(data, "Malloc error\n");
		check_and_add_texture(data, tmp);
		if (!ft_strcmp(tmp[0], "F"))
		{
			if (data->floor != -1)
				cub3d_err(data, "Mutiple color definitions for Floor\n");
			data->floor = get_color(data, tmp);
		}
		else if (!ft_strcmp(tmp[0], "C"))
		{
			if (data->ceiling != -1)
				cub3d_err(data, "Mutiple color definitions for Ceiling\n");
			data->ceiling = get_color(data, tmp);
		}
		free_array((void **)tmp);
	}
}
