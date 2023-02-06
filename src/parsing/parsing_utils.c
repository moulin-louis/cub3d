/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:56:27 by mpignet           #+#    #+#             */
/*   Updated: 2023/02/06 14:36:48 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_color(t_data *data, char **tmp)
{
	int		color;
	char	**buff;

	buff = ft_split(tmp[1], ',');
	if (!buff)
		cub3d_err(data, "Malloc error\n");
	else if (array_len((void **)buff) != 3)
	{
		free_array((void **)tmp);
		free_array((void **)buff);
		cub3d_err(data, "Color description error : format needed: r, g, b\n");
	}
	color = get_rgba(ft_atoi(buff[0]), ft_atoi(buff[1]), ft_atoi(buff[2]), 255);
	return (free_array((void **)buff), color);
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

int	get_nbr_lines(int fd)
{
	int		nbr;
	char	*line;

	nbr = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		nbr++;
	}
	return (nbr);
}

int	array_len(void **array)
{
	int	i;

	if (!array)
		return (0);
	i = 0;
	while (array[i])
		i++;
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;
	int	ls1;
	int	ls2;

	if (!s1 || !s2)
		return (1);
	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	if (ls1 != ls2)
		return (1);
	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}
