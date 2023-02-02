/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:40:57 by mpignet           #+#    #+#             */
/*   Updated: 2022/09/06 16:38:54 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	ft_nbr_len(long nb)
{
	int	len;

	len = 0;
	if (nb <= 0)
	{
		len = 1;
		nb = -nb;
	}
	while (nb > 0)
	{
		len = len + 1;
		nb = nb / 10;
	}
	return (len);
}

static void	ft_fill(char *tab, long nb, int len)
{
	if (nb < 0)
	{
		nb = -nb;
		while (len > 0)
		{
			tab[len - 1] = nb % 10 + 48;
			nb /= 10;
			len--;
		}
		tab[0] = '-';
	}
	else
	{
		while (len > 0)
		{
			tab[len - 1] = nb % 10 + 48;
			nb /= 10;
			len--;
		}
	}
}

char	*ft_itoa(int nbr)
{
	char	*tab;
	int		len;
	long	nb;

	nb = (long)nbr;
	len = ft_nbr_len(nb);
	tab = malloc (sizeof(char) * (len + 1));
	if (!tab)
		return (NULL);
	tab[len] = '\0';
	ft_fill(tab, nb, len);
	return (tab);
}
