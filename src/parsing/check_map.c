/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:39:50 by mpignet           #+#    #+#             */
/*   Updated: 2023/02/23 12:46:34 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_box(t_data *data, int i, size_t j)
{
	if (i < (data->end_index - 1) && ft_strlen(data->tmp_map[i + 1]) >= j
		&& data->tmp_map[i + 1][j])
	{		
		if (data->tmp_map[i + 1][j] != '1' && data->tmp_map[i + 1][j] != ' ')
			cub3d_err(data, "Map not properly closed !\n");
	}
	if (i > data->map_index && ft_strlen(data->tmp_map[i - 1]) >= j
		&& data->tmp_map[i - 1][j])
	{	
		if (data->tmp_map[i - 1][j] != '1' && data->tmp_map[i - 1][j] != ' ')
			cub3d_err(data, "Map not properly closed !\n");
	}
	if (j > 0)
	{				
		if (data->tmp_map[i][j - 1] != '1' && data->tmp_map[i][j - 1] != ' ')
			cub3d_err(data, "Map not properly closed !\n");
	}
	if (j < ft_strlen(data->tmp_map[i]) - 1)
	{
		if (data->tmp_map[i][j + 1] != '1' && data->tmp_map[i][j + 1] != ' ')
			cub3d_err(data, "Map not properly closed !\n");
	}
}

static void	check_line(t_data *data, int i)
{
	size_t	j;

	j = 0;
	if (ft_strlen(data->tmp_map[i]) == 0)
		return ;
	while (data->tmp_map[i][j])
	{
		if (data->tmp_map[i][j] == ' ')
			check_box(data, i, j);
		else if (data->tmp_map[i][j] == '0')
			check_box_zero(data, i, j);
		if (i == data->map_index || i == data->end_index - 1)
			if (data->tmp_map[i][j] != '1' && data->tmp_map[i][j] != ' ')
				cub3d_err(data, "Map not properly closed !\n");
		j++;
	}
}

int	check_around_player(t_data *data, int i, size_t j)
{
	if (ft_strlen(data->tmp_map[i + 1]) <= j
		|| ft_strlen(data->tmp_map[i - 1]) <= j)
		cub3d_err(data, "Map not properly closed !\n");
	if (i < (data->end_index - 1) && ft_strlen(data->tmp_map[i + 1]) > j
		&& data->tmp_map[i + 1][j])
	{
		if (data->tmp_map[i + 1][j] != '1' && data->tmp_map[i + 1][j] != ' '
		&& data->tmp_map[i + 1][j] != '0')
			cub3d_err(data, "Map not properly closed !\n");
	}
	if (i > data->map_index && ft_strlen(data->tmp_map[i - 1]) > j
		&& data->tmp_map[i - 1][j])
	{
		if (data->tmp_map[i - 1][j] != '1' && data->tmp_map[i - 1][j] != ' '
			&& data->tmp_map[i - 1][j] != '0')
			cub3d_err(data, "Map not properly closed !\n");
	}
	return (1);
}

static void	check_char(t_data *data)
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
			if (data->tmp_map[i][j] == 'N' || data->tmp_map[i][j] == 'S'
				|| data->tmp_map[i][j] == 'W' || data->tmp_map[i][j] == 'E')
				player += check_around_player(data, i, j);
			j++;
		}
		i++;
	}
	if (player != 1)
		cub3d_err(data, "Wrong number of players !\n");
}

int	check_map(t_data *data)
{
	int				i;
	unsigned int	end;
	int				begin;

	i = data->map_index - 1;
	check_char(data);
	while (data->tmp_map[++i])
	{
		check_line(data, i);
		end = ft_strlen(data->tmp_map[i]) - 1;
		begin = 0;
		while (data->tmp_map[i][begin] == ' ')
			begin++;
		if (data->tmp_map[i][begin] != '1' ||
			(data->tmp_map[i][end] != '1' && data->tmp_map[i][end] != ' '))
			cub3d_err(data, "Map not properly closed !\n");
	}
	return (0);
}
