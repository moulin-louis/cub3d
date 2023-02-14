/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:40:42 by mpignet           #+#    #+#             */
/*   Updated: 2023/02/14 12:22:50 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	get_map_len(t_data *data)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (data->tmp_map[i])
	{
		if (data->tmp_map[i] && (data->tmp_map[i][0] == '1'
			|| data->tmp_map[i][0] == ' '))
		{
			data->map_index = i;
			while (data->tmp_map[i] && (data->tmp_map[i][0] == '1'
				|| data->tmp_map[i][0] == ' '))
			{
				len++;
				i++;
			}
			data->end_index = data->map_index + len;
			return (len);
		}
		i++;
	}
	return (cub3d_err(data, "No map in file\n"), 0);
}

static int	set_player_dir(t_data *data, char dir)
{
	if (dir == 'N')
	{
		data->dir_x = -1;
		data->dir_y = 0;
		data->plane_x = 0;
		data->plane_y = FOV;
		return (0);
	}
	else if (dir == 'S')
	{
		data->dir_x = 1;
		data->dir_y = 0;
		data->plane_x = 0;
		data->plane_y = -FOV;
		return (0);
	}
	else if (dir == 'W')
	{
		data->dir_x = 0;
		data->dir_y = -1;
		data->plane_x = -FOV;
		return (data->plane_y = 0, 0);
	}
	return (data->dir_x = 0, data->dir_y = 1, data->plane_x = FOV,
		data->plane_y = 0, 0);
}

static void	set_player_start_pos(t_data *data, int i, int k, int j)
{
	data->map[k][j] = 0;
	data->pos_x = (double)k + 0.5;
	data->pos_y = (double)j + 0.5;
	if (data->tmp_map[i][j] == 'N')
		set_player_dir(data, 'N');
	else if (data->tmp_map[i][j] == 'S')
		set_player_dir(data, 'S');
	else if (data->tmp_map[i][j] == 'W')
		set_player_dir(data, 'W');
	else if (data->tmp_map[i][j] == 'E')
		set_player_dir(data, 'E');
}

static void	set_map_line(t_data *data, int i, int k)
{
	int	j;

	j = -1;
	while (data->tmp_map[i][++j])
	{
		if (data->tmp_map[i][j] == 'N' || data->tmp_map[i][j] == 'S'
			|| data->tmp_map[i][j] == 'W' || data->tmp_map[i][j] == 'E')
			set_player_start_pos(data, i, k, j);
		else if (data->tmp_map[i][j] == ' ')
			data->map[k][j] = SPACE;
		else
			data->map[k][j] = data->tmp_map[i][j] - 48;
	}
}

void	add_map(t_data *data)
{
	int		i;
	int		k;
	int		len;

	len = get_map_len(data);
	check_empty_line(data);
	check_map(data);
	data->map = malloc(sizeof(int *) * (len + 1));
	if (!data->map)
		cub3d_err(data, "Malloc error\n");
	data->map[len] = NULL;
	i = data->map_index;
	k = 0;
	while (data->tmp_map[i])
	{
		len = ft_strlen(data->tmp_map[i]);
		data->map[k] = malloc(sizeof(int) * (len + 1));
		if (!data->map[k])
			cub3d_err(data, "malloc failed\n");
		data->map[k][len] = END;
		set_map_line(data, i, k);
		i++;
		k++;
	}
}
