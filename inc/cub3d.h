/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:04:16 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/06 13:34:02 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include <time.h>
# include "libft.h"
# include "MLX42.h"

# define FOV 80
# define WIDTH 1280
# define HEIGHT 720
# define SPACE 9
# define END 42
# define START_N 2
# define START_S 3
# define START_W 4
# define START_E 5

typedef struct s_data
{
	mlx_t		*mlx;
	int			floor;
	int			ceiling;
	mlx_image_t	*img;

	mlx_image_t	*nord;
	mlx_image_t	*south;
	mlx_image_t	*west;
	mlx_image_t	*east;

	int			map_index;
	char		**tmp_map;
	int			**map;

	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;

}	t_data;

/*----------------------------------PARSING--------------------------------*/

t_data	parsing(char *path_map);
void	add_map(t_data *data);

int		check_file_name(char *file);
int		check_map(t_data *data);

/*----------------------------------RENDRING-------------------------------*/

void	rendering(void *data);
int		get_rgb(int r, int g, int b);
void	camera(void *ptr);

/*-----------------------------------COLOR---------------------------------*/
int		get_r(int rgba);
int		get_g(int rgba);
int		get_b(int rgba);
int		get_a(int rgba);
int		get_rgba(int r, int g, int b, int a);

/*-----------------------------------UTILS---------------------------------*/

int		ft_strcmp(const char *s1, const char *s2);
int		array_len(void **array);
int		get_nbr_lines(int fd);

/*-----------------------------------ERROR---------------------------------*/

void	mlx_err(t_data *data);
void	cub3d_err(t_data *data, char *err);
void	free_array(void **array);
void	close_prog(void *ptr);

#endif