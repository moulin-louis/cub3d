/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:19:10 by mpignet           #+#    #+#             */
/*   Updated: 2022/09/07 14:39:17 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	ft_dispatch(const char c, va_list arg, size_t len)
{
	if (c == 'c')
		len += ft_printchar(va_arg(arg, int));
	else if (c == 's')
		len += ft_printstr(va_arg(arg, char *));
	else if (c == 'p')
		len += ft_print_ptr(va_arg(arg, unsigned long long));
	else if (c == 'd' || c == 'i')
		len += ft_printnbr(va_arg(arg, int));
	else if (c == 'u')
		len += ft_printnbr_unsigned(va_arg(arg, unsigned int));
	else if (c == 'x')
		len += ft_printhexa(va_arg(arg, unsigned int), 0);
	else if (c == 'X')
		len += ft_printhexa(va_arg(arg, unsigned int), 1);
	else if (c == '%')
	{
		ft_putchar(c);
		len++;
	}
	return (len);
}

int	ft_printf(const char *entree, ...)
{
	va_list	arg;
	size_t	i;
	size_t	len;

	va_start (arg, entree);
	i = 0;
	len = 0;
	while (entree[i])
	{
		if (entree[i] == '%')
		{
			i++;
			if (!entree[i])
				break ;
			len = ft_dispatch(entree[i], arg, len);
		}
		else
		{
			ft_putchar(entree[i]);
			len++;
		}
		i++;
	}
	va_end(arg);
	return (len);
}
