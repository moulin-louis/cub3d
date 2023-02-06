/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:39:50 by mpignet           #+#    #+#             */
/*   Updated: 2023/02/06 12:39:46 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_line(t_data *data, int i)
{
	size_t	j;

	j = 0;
	while (data->tmp_map[i][j])
	{
		if (data->tmp_map[i][j] == ' ')
		{
			if (i == data->map_index)
			{				
				if (data->tmp_map[i + 1][j] != '1' && data->tmp_map[i + 1][j] != ' ')
					cub3d_err(data, "Map not properly closed !\n");
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
		}
		if (data->tmp_map[i][j] != '1' && data->tmp_map[i][j] != ' ')
			cub3d_err(data, "Map not properly closed !\n");
		j++;
	}
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
	int	end;
	int	begin;

	i = data->map_index - 1;
	check_char(data);
	while(data->tmp_map[++i])
	{
		end = ft_strlen(data->tmp_map[i]) - 1;
		begin = 0;
		while (data->tmp_map[i][begin] == ' ')
			begin++;
		if (data->tmp_map[i][begin] != '1' || data->tmp_map[i][end] != '1')
			cub3d_err(data, "Map not properly closed\n");
	}
	check_line(data, data->map_index);
	check_line(data, (i - 1));
	return (0);
}