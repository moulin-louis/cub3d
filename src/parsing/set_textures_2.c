/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:43:50 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/23 12:43:50 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_ea(t_data *data, char **tmp)
{
	if (!ft_strcmp(tmp[0], "EA"))
	{
		if (data->east.img)
			free_arr_exit(tmp, data, "Mutiple path def for East walls\n");
		check_xpm_file(data, tmp);
		add_tex_path(data, tmp, "EA");
		data->east.img = mlx_xpm_file_to_image(data->mlx, tmp[1],
				&data->east.width, &data->east.height);
		if (data->east.img == NULL)
			free_arr_exit(tmp, data, "failed load xpm\n");
		data->east.addr = mlx_get_data_addr(data->east.img,
				&data->east.bpp, &data->east.size_line, &data->east.endian);
	}
}

void	add_so(t_data *data, char **tmp)
{
	if (!ft_strcmp(tmp[0], "SO"))
	{
		if (data->south.img)
			free_arr_exit(tmp, data, "Mutiple path def for South walls\n");
		check_xpm_file(data, tmp);
		add_tex_path(data, tmp, "SO");
		data->south.img = mlx_xpm_file_to_image(data->mlx, tmp[1],
				&data->south.width, &data->south.height);
		if (data->south.img == NULL)
			free_arr_exit(tmp, data, "failed load xpm\n");
		data->south.addr = mlx_get_data_addr(data->south.img,
				&data->south.bpp, &data->south.size_line, &data->south.endian);
	}
}
