/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:04:16 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/14 16:24:44 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/inc/libft.h"
# include "../lib/minilibx-linux/mlx.h"
# include "../lib/minilibx-linux/mlx_int.h"
# include <stdbool.h>
# include <math.h>
# include <sys/time.h>

# define FOV 0.66
# define WIDTH 1920
# define HEIGHT 1080
# define SPACE 9
# define END 42

typedef struct s_tex
{
	void	*img;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_tex;

typedef struct s_img_data
{
	t_img	*img;
	char	*raw_data;
	int		size_line;
	int		bpp;
	int		endian;
}	t_img_data;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	int		floor;
	int		ceiling;

	char	*path_no;
	char	*path_so;
	char	*path_we;
	char	*path_ea;

	t_tex	nord;
	t_tex	south;
	t_tex	west;
	t_tex	east;

	int		map_index;
	int		end_index;
	char	**tmp_map;
	int		**map;

	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;

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
	int				current_x;
	int				color;
}	t_math;

/*----------------------------------PARSING--------------------------------*/

t_data	parsing(char *path_map);
void	add_map(t_data *data);
int		check_map(t_data *data);
void	add_textures_and_colors(t_data *data);
void	check_texture_color_error(t_data *data);
void	check_xpm_file(t_data *data, char **tmp);
void	add_tex_path(t_data *data, char **tmp, char *side);
void	check_invalid_info(t_data *data, char **tmp);
void	check_box_zero(t_data *data, int i, size_t j);
void	add_ea(t_data *data, char **tmp);
void	add_so(t_data *data, char **tmp);

/*----------------------------------RENDRING-------------------------------*/

int		rendering(void *data);
int		camera(int key, void *ptr);
void	draw_line(t_math *math, t_data *data, int x);
void	calculate_draw_start_end(t_math *math);
void	perform_dda(t_math *math, t_data *data);
void	calculate_step(t_math *math, t_data *data);
void	calculate_init(t_math *math, t_data *data, int x);

/*-----------------------------------COLOR---------------------------------*/

int		get_rgb(unsigned int red, unsigned int green, unsigned int blue);
void	img_pix_put(t_img_data *img_data, int x, int y, int color);

/*----------------------------------TEXTURE---------------------------------*/

int		get_pixel(t_tex tex, int x, int y);
void	get_tex_line(t_data *data, t_tex tex, t_math *math, t_img_data *img_d);
void	draw_text_line(t_data *data, t_math *math, t_img_data *img_data);

/*-----------------------------------UTILS---------------------------------*/

int		ft_strcmp(const char *s1, const char *s2);
int		array_len(void **array);
int		get_nbr_lines(int fd);
int		check_file_name(const char *file);
float	calculate_buffer_zone_x(t_data *data);
float	calculate_buffer_zone_y(t_data *data);
bool	ut_atoi(unsigned int *nbr, const char *str);
int		check_color(char **buff);
void	free_arr_exit(char **ar, t_data *data, char *err);
void	check_empty_line(t_data *data);

/*-----------------------------------ERROR---------------------------------*/

void	mlx_err(t_data *data);
void	cub3d_err(t_data *data, char *err);
void	free_array(void **array);
int		close_prog(void *ptr);

#endif