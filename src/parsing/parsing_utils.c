/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:56:27 by mpignet           #+#    #+#             */
/*   Updated: 2023/02/13 14:24:29 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	ut_atoi(int *nbr, const char *str)
{
	int	nbr_tmp;
	int	nbr_tmp2;
	int	i;

	*nbr = 0;
	while (*str != '\0' && *str >= '0' && *str <= '9')
	{
		i = 0;
		nbr_tmp2 = *nbr;
		while (i++ < 9)
		{
			nbr_tmp = *nbr;
			*nbr += nbr_tmp2;
			if (*nbr < nbr_tmp)
				return (false);
		}
		*nbr = *nbr + (*str - 48);
		str++;
	}
	return (true);
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
