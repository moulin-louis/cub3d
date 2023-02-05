/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:39:50 by mpignet           #+#    #+#             */
/*   Updated: 2023/02/05 15:09:27 by mpignet          ###   ########.fr       */
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

/* int	check_exit(t_data *data)
{
	int	i;
	int	j;
	int	exit;

	i = 0;
	exit = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'E')
				exit++;
			else if (data->map[i][j] != '0' && data->map[i][j] != '1'
				&& data->map[i][j] != 'C' && data->map[i][j] != 'P')
				return (ft_putstr_fd("Error\nInvalid char in map\n", 2), 1);
			j++;
		}
		i++;
	}
	if (exit != 1)
		return (ft_putstr_fd("Error\nWrong number of exits\n", 2), 1);
	return (0);
} */

int	check_empty_lines(char *line)
{
	int	i;

	i = 1;
	while (line[i])
	{
		if (line[i] == '\n' && line[i - 1] == '\n')
			return (ft_putstr_fd("Error\nEmpty line in map\n", 2), 1);
		i++;
	}
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