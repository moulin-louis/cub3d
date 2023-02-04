/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:04:16 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/04 09:27:03 by loumouli         ###   ########.fr       */
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
# include "MLX42.h"

# define FOV 80
# define WIDTH 1280
# define HEIGHT 720

typedef struct s_data
{
	mlx_t	*mlx;

	int	floor;
	int	ceiling;
	mlx_image_t* img[WIDTH];

	mlx_image_t	*nord;
	mlx_image_t	*south;
	mlx_image_t	*west;
	mlx_image_t	*east;

	double	**map;
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
}	t_data;

/*----------------------------------PARSING--------------------------------*/

t_data	parsing(char *path_map);
int		check_file_name(char *file);
int		check_walls(t_data *data);

/*----------------------------------RENDRING-------------------------------*/

void	rendering( void* data);
int 	get_rgb(int r, int g, int b);

/*-----------------------------------UTILS---------------------------------*/

int		ft_strcmp(const char *s1, const char *s2);
int		array_len(void **array);

/*-----------------------------------ERROR---------------------------------*/

void	mlx_err(t_data *data);
void	cub3d_err(t_data *data, char *err);
void	free_array(void **array);

#endif