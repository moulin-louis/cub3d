/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:39:50 by mpignet           #+#    #+#             */
/*   Updated: 2023/02/05 19:10:05 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_walls_line(t_data *data, int i)
{
	int	j;

	j = 0;
	while (data->tmp_map[i][j])
	{
		if (data->tmp_map[i][j] != '1')
			return (1);
		j++;
	}
	return (0);
}

int	check_walls(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[i + 1])
	{
		j = 0;
		while (data->map[i][j + 1])
		{
			if (data->map[i][0] != '1')
				return (ft_putstr_fd("Error\nMissing wall in map\n", 2), 1);
			j++;
		}
		if (data->map[i][j] != '1')
			return (ft_putstr_fd("Error\nMissing wall in map\n", 2), 1);
		i++;
	}
	if (check_walls_line (data, 0) || check_walls_line (data, i))
		return (ft_putstr_fd("Error\nMissing wall in map\n", 2), 1);
	return (0);
}

int	check_char(t_data *data)
{
	int	i;
	int	j;
	int	player;

	i = data->map_index;
	player = 0;
	while (data->tmp_map[i])
	{
		j = 0;
		while (data->tmp_map[i][j])
		{
			if (data->tmp_map[i][j] != ' ' && data->tmp_map[i][j] != '0'
				&& data->tmp_map[i][j] != '1' && data->tmp_map[i][j] != 'N'
				&& data->tmp_map[i][j] != 'S' && data->tmp_map[i][j] != 'W'
				&& data->tmp_map[i][j] != 'E')
				cub3d_err(data, "Invalid char in map !\n");
			if(data->tmp_map[i][j] == 'N' || data->tmp_map[i][j] == 'S'
				|| data->tmp_map[i][j] == 'W' || data->tmp_map[i][j] == 'E')
				player++;
			j++;
		}
		i++;
	}
	if (player != 1)
		cub3d_err(data, "Wrong number of players !\n");
	return (0);
}

int	check_file_name(char *file)
{
	size_t	i;

	i = 0;
	while (file[i])
		i++;
	if (i < 4)
		return (1);
	else if (file[i - 4] == '.' && file[i - 3] == 'c'
		&& file[i - 2] == 'u' && file[i - 1] == 'b')
		return (0);
	return (1);
}

int	check_map(t_data *data)
{
	int	i;
	int	j;
	int	begin;

	i = data->map_index - 1;
	check_char(data);
	while(data->tmp_map[++i])
	{
		j = 0;
		while (data->tmp_map[i][j])
			j++;
		j--;
		begin = 0;
		while (data->tmp_map[i][begin] == ' ')
			begin++;
		if (data->tmp_map[i][begin] != '1' || data->tmp_map[i][j] != '1')
			cub3d_err(data, "Map not properly closed\n");
	}
	return (0);
}