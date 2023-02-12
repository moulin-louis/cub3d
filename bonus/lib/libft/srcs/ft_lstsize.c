/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:13:29 by mpignet           #+#    #+#             */
/*   Updated: 2022/09/06 16:39:24 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_lstsize(t_list *lst)
{
	int	nb;

	if (!lst)
		return (0);
	nb = 0;
	while (lst)
	{
		lst = lst->next;
		nb++;
	}
	return (nb);
}
