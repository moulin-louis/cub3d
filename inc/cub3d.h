/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:04:16 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/03 15:56:35 by loumouli         ###   ########.fr       */
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
#include <time.h>
# include "libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# define FOV 80
# define WIDTH 640
# define HEIGHT 480

typedef struct s_map
{
	void	*mlx;
	void	*window;

	int	floor;
	int	ceiling;
	mlx_image_t* img[WIDTH];

	void	*nord;
	void	*south;
	void	*east;
	void	*west;

	char	**map;
}	t_map;

int		parsing(char *path_map);
void	rendering( void* data);
int get_rgba(int r, int g, int b);
#endif