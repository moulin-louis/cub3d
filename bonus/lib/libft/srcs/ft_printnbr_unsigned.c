/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr_unsigned.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:30:29 by mpignet           #+#    #+#             */
/*   Updated: 2022/09/07 14:39:22 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	ft_nbrlen_unsigned(unsigned int nbr)
{
	int	i;

	i = 0;
	if (nbr == 0)
		return (1);
	while (nbr != 0)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

int	ft_printnbr_unsigned(unsigned int n)
{
	unsigned int	i;

	i = n;
	if (i > 9)
	{
		ft_printnbr_unsigned(i / 10);
		i = i % 10;
	}
	ft_putchar('0' + i);
	return (ft_nbrlen_unsigned(n));
}
