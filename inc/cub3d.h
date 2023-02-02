/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:04:16 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/02 14:02:29 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>
#include "libft.h"

typedef struct s_map
{
	void	*mlx;
	void	*window;

	unsigned char	floor[3];
	unsigned char	ceiling[3];

	void	*nord;
	void	*south;
	void	*east;
	void	*west;

	char	**map;
	int		win_width;
	int		win_height;
}	t_map;

int	parsing(char *path_map);

#endif