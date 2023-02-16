/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:13:55 by mpignet           #+#    #+#             */
/*   Updated: 2023/02/16 17:23:04 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	check_double_texture(t_data *data, char **tmp)
{
	if (!ft_strcmp(data->path_no, tmp[1]) || !ft_strcmp(data->path_so, tmp[1])
		|| !ft_strcmp(data->path_we, tmp[1])
		|| !ft_strcmp(data->path_ea, tmp[1]))
	{
		free_array((void **)tmp);
		cub3d_err(data, "Same texture twice\n");
	}
}

void	add_others(t_data *data, char **tmp, char *side)
{
	if (!ft_strcmp(side, "WE"))
	{
		data->path_we = ft_strdup(tmp[1]);
		if (!data->path_we)
		{
			free_array((void **)tmp);
			cub3d_err(data, "Malloc error\n");
		}
	}
	if (!ft_strcmp(side, "EA"))
	{
		data->path_ea = ft_strdup(tmp[1]);
		if (!data->path_ea)
		{
			free_array((void **)tmp);
			cub3d_err(data, "Malloc error\n");
		}
	}
}

void	add_tex_path(t_data *data, char **tmp, char *side)
{
	check_double_texture(data, tmp);
	if (!ft_strcmp(side, "SO"))
	{
		data->path_so = ft_strdup(tmp[1]);
		if (!data->path_so)
		{
			free_array((void **)tmp);
			cub3d_err(data, "Malloc error\n");
		}
	}
	if (!ft_strcmp(side, "NO"))
	{
		data->path_no = ft_strdup(tmp[1]);
		if (!data->path_no)
		{
			free_array((void **)tmp);
			cub3d_err(data, "Malloc error\n");
		}
	}
	add_others(data, tmp, side);
}

int	check_file_name_xpm(char *file)
{
	size_t	i;

	i = 0;
	if (!file)
		return (1);
	while (file[i])
		i++;
	if (i < 4)
		return (1);
	else if (file[i - 4] == '.' && file[i - 3] == 'x'
		&& file[i - 2] == 'p' && file[i - 1] == 'm')
		return (0);
	return (1);
}

void	check_xpm_file(t_data *data, char **tmp)
{
	int	fd;

	if (check_file_name_xpm(tmp[1]))
	{
		free_array((void **)tmp);
		cub3d_err(data, "Wall texture files need to be .xpm\n");
	}
	fd = open(tmp[1], O_RDWR);
	if (fd == -1)
	{
		free_array((void **)tmp);
		cub3d_err(data, "Open error on wall texture file\n");
	}
	close(fd);
}
