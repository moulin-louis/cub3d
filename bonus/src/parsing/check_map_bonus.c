/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:39:50 by mpignet           #+#    #+#             */
/*   Updated: 2023/02/14 12:24:05 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	check_box(t_data *data, int i, size_t j)
{
	if (data->tmp_map[i + 1] && data->tmp_map[i + 1][j])
	{		
		if (data->tmp_map[i + 1][j] != '1' && data->tmp_map[i + 1][j] != ' ')
			cub3d_err(data, "Map not properly closed !\n");
	}
	if (i > data->map_index && data->tmp_map[i - 1][j])
	{	
		if (data->tmp_map[i - 1][j] != '1' && data->tmp_map[i - 1][j] != ' ')
			cub3d_err(data, "Map not properly closed !\n");
	}
	if (j > 0)
	{				
		if (data->tmp_map[i][j - 1] != '1' && data->tmp_map[i][j - 1] != ' ')
			cub3d_err(data, "Map not properly closed !\n");
	}
	if (j < ft_strlen(data->tmp_map[i]))
	{
		if (data->tmp_map[i][j + 1] != '1' && data->tmp_map[i][j + 1] != ' ')
			cub3d_err(data, "Map not properly closed !\n");
	}
}

static void	check_box_zero(t_data *data, int i, size_t j)
{
	if (data->tmp_map[i + 1] && !data->tmp_map[i + 1][j])
		cub3d_err(data, "Map not properly closed !\n");
	if (i > data->map_index && !data->tmp_map[i - 1][j])
		cub3d_err(data, "Map not properly closed !\n");
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
				player++;
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
		if (data->tmp_map[i][begin] != '1' || data->tmp_map[i][end] != '1')
			cub3d_err(data, "Map not properly closed\n");
	}
	return (0);
}
