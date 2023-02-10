/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:04:16 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/08 16:47:23 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../lib/libft/inc/libft.h"
# include "../lib/minilibx-linux/mlx.h"
# include "../lib/minilibx-linux/mlx_int.h"
# include <math.h>
# include <sys/time.h>

# define FOV 0.66
# define WIDTH 1280
# define HEIGHT 720
# define SPACE 9
# define END 42
# define START_N 2
# define START_S 3
# define START_W 4
# define START_E 5
# define RED get_rgb(255, 0, 0)
# define GREEN get_rgb(0, 255, 0)
# define BLACK get_rgb(0, 0, 0)
# define WHITE get_rgb(255, 255, 255)

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	int		floor;
	int		ceiling;

	void	*nord;
	void	*south;
	void	*west;
	void	*east;

	int		map_index;
	int		end_index;
	char	**tmp_map;
	int		**map;
	int 	len_map_x;
	int 	len_map_y;

	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;

}	t_data;

typedef struct	s_img_data
{
	t_img	*img;
	char	*raw_data;
	int 	size_line;
	int 	bpp;
	int 	endian;
}	t_img_data;

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
	int				color;
}	t_math;

/*----------------------------------PARSING--------------------------------*/

t_data	parsing(char *path_map);
void	add_map(t_data *data);
int		check_map(t_data *data);
void	add_textures_and_colors(t_data *data);
void	check_texture_color_error(t_data *data);

/*----------------------------------RENDRING-------------------------------*/

int		rendering(void *data);
int		camera(int key, void *ptr);
void	draw_line(t_math *math, t_data *data, int x);
void	calculate_draw_start_end(t_math *math);
void	perform_dda(t_math *math, t_data *data);
void	calculate_step(t_math *math, t_data *data);
void	calculate_init(t_math *math, t_data *data, int x);
void	draw_minimap(t_data *data);

/*-----------------------------------COLOR---------------------------------*/
int		get_rgb(int red, int green, int blue);
void	check_side(t_data *data, t_math *math);
void	img_pix_put(t_img_data *img_data, int x, int y, int color);

/*-----------------------------------UTILS---------------------------------*/

int		ft_strcmp(const char *s1, const char *s2);
int		array_len(void **array);
int		get_nbr_lines(int fd);
int		check_file_name(char *file);

/*-----------------------------------ERROR---------------------------------*/

void	mlx_err(t_data *data);
void	cub3d_err(t_data *data, char *err);
void	free_array(void **array);
int		close_prog(void *ptr);

#endif