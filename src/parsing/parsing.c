/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:34:07 by mpignet           #+#    #+#             */
/*   Updated: 2023/02/02 17:52:02 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_data	*init_data(t_data *data)
{
	data = ft_calloc(sizeof(t_data), 1);
	if (!data)
		return(ft_putstr_fd("Error\nMalloc failed\n", 2), exit(EXIT_FAILURE),
			NULL);
	return(data);
}

t_data	*parse_file(t_data *data, char *path_file)
{
	int	fd;

	(void)data;
	fd = open(path_file, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error\nFailed opening file\n", 2), exit(errno),
			NULL);
	return (data);
}

t_data	*parsing(char *path_map)
{
	t_data	*data;
	
	data = NULL;
	data = init_data(data);
	data = parse_file(data, path_map);
	return (NULL);
}