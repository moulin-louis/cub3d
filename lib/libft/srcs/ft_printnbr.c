/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:06:03 by mpignet           #+#    #+#             */
/*   Updated: 2022/09/07 14:39:25 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	ft_nbrlen(int nbr)
{
	int	i;

	i = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
		i++;
	while (nbr != 0)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

int	ft_printnbr(int n)
{
	int	i;

	if (n < 0 && n > -2147483648)
	{
		ft_putchar('-');
		i = -n;
	}
	else
		i = n;
	if (i > 9)
	{
		ft_printnbr(i / 10);
		i = i % 10;
	}
	if (n == -2147483648)
	{
		write (1, "-2147483648", 11);
	}
	else
		ft_putchar('0' + i);
	return (ft_nbrlen(n));
}
