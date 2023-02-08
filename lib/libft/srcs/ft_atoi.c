/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 11:57:59 by mpignet           #+#    #+#             */
/*   Updated: 2023/02/02 13:49:18 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	check_str(const char *str)
{
	int	i;

	i = 0;
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	nbr;
	int	nbr_tmp;
	int	nbr_tmp2;
	int	i;

	nbr = 0;
	if (check_str(str))
		return (-1);
	while (*str != '\0' && *str >= '0' && *str <= '9')
	{
		i = 0;
		nbr_tmp2 = nbr;
		while (i++ < 9)
		{
			nbr_tmp = nbr;
			nbr += nbr_tmp2;
			if (nbr < nbr_tmp)
				return (-1);
		}
		nbr = nbr + (*str - 48);
		str++;
	}
	return (nbr);
}
