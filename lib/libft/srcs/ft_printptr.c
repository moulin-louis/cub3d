/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:26:23 by mpignet           #+#    #+#             */
/*   Updated: 2022/09/07 14:39:28 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	ft_getlen(unsigned long ptr)
{
	int	i;

	i = 0;
	if (ptr == 0)
		return (1);
	while (ptr != 0)
	{
		ptr /= 16;
		i++;
	}
	return (i);
}

static int	ft_conv_hexa(unsigned long ptr, char *base)
{
	if (ptr > 15)
		ft_conv_hexa(ptr / 16, base);
	ft_putchar(base[ptr % 16]);
	return (ft_getlen(ptr));
}

int	ft_print_ptr(unsigned long ptr)
{
	int		len;
	char	*base;

	base = "0123456789abcdef";
	if (ptr == 0)
	{
		write (1, "(nil)", 5);
		return (5);
	}
	write (1, "0x", 2);
	len = 2;
	len += ft_conv_hexa(ptr, base);
	return (len);
}
