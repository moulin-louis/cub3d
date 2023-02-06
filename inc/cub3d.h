/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:04:16 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/06 14:02:19 by loumouli         ###   ########.fr       */
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

typedef struct s_math
{
	double			camera_x;
	double			ray_dirx;
	double			ray_diry;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	unsigned int	draw_start;
	unsigned int	draw_end;
}	t_math;

/*----------------------------------PARSING--------------------------------*/

t_data	parsing(char *path_map);
void	add_map(t_data *data);

int		check_file_name(char *file);
int		check_map(t_data *data);
int		check_walls(t_data *data);
/*----------------------------------RENDRING-------------------------------*/

void	rendering(void *data);
int		get_rgb(int r, int g, int b);
void	camera(void *ptr);
void	draw_line(t_math *math, t_data *data, int x);
void	calculate_draw_start_end(t_math *math);
void	perform_dda(t_math *math, t_data *data);
void	calculate_step(t_math *math, t_data *data);
void	calculate_init(t_math *math, t_data *data, int x);

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