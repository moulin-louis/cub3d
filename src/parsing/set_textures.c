/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:03:51 by mpignet           #+#    #+#             */
/*   Updated: 2023/02/16 15:07:08 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_color(t_data *data, char **tmp)
{
	int				color;
	char			**buff;

	buff = ft_split(tmp[1], ',');
	if (!buff)
		free_arr_exit(tmp, data, "split color error\n");
	else if (array_len((void **)buff) != 3)
	{
		free_array((void **)tmp);
		free_array((void **)buff);
		cub3d_err(data, "Color description error : format needed: r, g, b\n");
	}
	color = check_color(buff);
	if (color == -1)
	{
		free_array((void **)tmp);
		free_array((void **)buff);
		cub3d_err(data, "Color description error : format needed: r, g, b\n");
	}
	return (free_array((void **)buff), color);
}

void	add_we_ea(t_data *data, char **tmp)
{
	if (!ft_strcmp(tmp[0], "WE"))
	{
		if (data->west.img)
			free_arr_exit(tmp, data, "Mutiple path def for West walls\n");
		check_xpm_file(data, tmp);
		add_tex_path(data, tmp, "WE");
		data->west.img = mlx_xpm_file_to_image(data->mlx, tmp[1],
				&data->west.width, &data->west.height);
		if (data->west.img == NULL)
			free_arr_exit(tmp, data, "failed load xpm\n");
		data->west.addr = mlx_get_data_addr(data->west.img,
				&data->west.bpp, &data->west.size_line,
				&data->west.endian);
	}
	add_ea(data, tmp);
}

static void	check_and_add_texture(t_data *data, char **tmp)
{
	if (!ft_strcmp(tmp[0], "NO"))
	{
		if (data->nord.img)
			free_arr_exit(tmp, data, "Mutiple path def for North walls\n");
		check_xpm_file(data, tmp);
		add_tex_path(data, tmp, "NO");
		data->nord.img = mlx_xpm_file_to_image(data->mlx, tmp[1],
				&data->nord.width, &data->nord.height);
		if (data->nord.img == NULL)
			free_arr_exit(tmp, data, "failed load xpm\n");
		data->nord.addr = mlx_get_data_addr(data->nord.img,
				&data->nord.bpp, &data->nord.size_line,
				&data->nord.endian);
	}
	add_so(data, tmp);
	add_we_ea(data, tmp);
}

int	add_color(t_data *data, char **tmp)
{
	if (!ft_strcmp(tmp[0], "F"))
	{
		if (data->floor != -1)
			return (free_array((void **)tmp),
				cub3d_err(data, "Mutiple color definitions for Floor\n"), 1);
		data->floor = get_color(data, tmp);
	}
	else if (!ft_strcmp(tmp[0], "C"))
	{
		if (data->ceiling != -1)
			return (free_array((void **)tmp),
				cub3d_err(data, "Mutiple color definitions for Ceiling\n"), 1);
		data->ceiling = get_color(data, tmp);
	}
	return (0);
}

void	add_textures_and_colors(t_data *data)
{
	int		i;
	char	**tmp;

	i = -1;
	while (data->tmp_map[++i])
	{
		if (data->tmp_map[i][0] != ' ' && data->tmp_map[i][0] != '1')
		{
			tmp = ft_split(data->tmp_map[i], ' ');
			if (!tmp)
				cub3d_err(data, "Malloc error\n");
			check_invalid_info(data, tmp);
			check_and_add_texture(data, tmp);
			add_color(data, tmp);
			free_array((void **)tmp);
		}
	}
}
