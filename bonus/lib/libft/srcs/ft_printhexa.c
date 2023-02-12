/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:46:30 by mpignet           #+#    #+#             */
/*   Updated: 2022/09/07 14:39:19 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	ft_hexlen(unsigned int nbr)
{
	int	i;

	i = 0;
	if (nbr == 0)
		return (1);
	while (nbr != 0)
	{
		nbr /= 16;
		i++;
	}
	return (i);
}

static void	ft_conv_print(unsigned int a, unsigned int size, char *base)
{
	if (a > size - 1)
		ft_conv_print(a / size, size, base);
	ft_putchar(base[a % size]);
}

int	ft_printhexa(unsigned int nbr, int format)
{
	char	*base;

	if (format == 0)
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	ft_conv_print(nbr, 16, base);
	return (ft_hexlen(nbr));
}
