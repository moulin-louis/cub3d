/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:49:44 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/13 14:50:35 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_color(char **buff)
{
	unsigned int	result[3];

	if (!ut_atoi(&result[0], buff[0]) || !ut_atoi(&result[1], buff[1])
		|| !ut_atoi(&result[2], buff[2]))
		return (-1);
	if ((result[0] > 255 || result[1] > 255 || result[2] > 255))
		return (-1);
	return (get_rgb(result[0], result[1], result[2]));
}

bool	ut_atoi(unsigned int *nbr, const char *str)
{
	int	nbr_tmp;
	int	nbr_tmp2;
	int	i;

	*nbr = 0;
	i = -1;
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (false);
	while (*str != '\0' && *str >= '0' && *str <= '9')
	{
		i = 0;
		nbr_tmp2 = *nbr;
		while (i++ < 9)
		{
			nbr_tmp = *nbr;
			*nbr += nbr_tmp2;
			if (*nbr < (unsigned int)nbr_tmp)
				return (false);
		}
		*nbr = *nbr + (*str - 48);
		str++;
	}
	return (true);
}
