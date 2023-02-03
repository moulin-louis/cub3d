/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:04:16 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/03 16:07:48 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>
#include <time.h>
# include "libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# define FOV 80
# define WIDTH 640
# define HEIGHT 480

typedef struct s_data
{
	mlx_t	*mlx;

	int	floor;
	int	ceiling;
	mlx_image_t* img[WIDTH];

	mlx_image_t	*nord;
	mlx_image_t	*south;
	mlx_image_t	*east;
	mlx_image_t	*west;

	double	**map;

	int		win_width;
	int		win_height;
}	t_data;

/*-----------------------------------PARSING--------------------------------*/

t_data	*parsing(char *path_map);

void	rendering( void* data);
int get_rgba(int r, int g, int b);
#endif