/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:34:07 by mpignet           #+#    #+#             */
/*   Updated: 2023/02/14 16:26:47 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	check_box_zero(t_data *data, int i, size_t j)
{
	if (data->tmp_map[i + 1]
		&& (ft_strlen(data->tmp_map[i + 1]) < j || !data->tmp_map[i + 1][j]))
		cub3d_err(data, "Map not properly closed !\n");
	if (i > data->map_index
		&& (ft_strlen(data->tmp_map[i - 1]) < j || !data->tmp_map[i - 1][j]))
		cub3d_err(data, "Map not properly closed !\n");
}

static void	fill_buffer(t_data *data, char **buff, int nbr_lines, int fd)
{
	int		i;
	char	*tmp;

	i = -1;
	while (++i < nbr_lines)
	{
		buff[i] = get_next_line(fd);
		if (!buff[i])
			return ;
		tmp = buff[i];
		buff[i] = ft_strtrim(buff[i], "\n");
		if (!buff[i])
		{			
			free(tmp);
			free_array((void **)buff);
			cub3d_err(data, "Failed opening file\n");
		}
		else
			free(tmp);
	}
}

static char	**parse_file(t_data *data, char *file)
{
	int		nbr_lines;
	int		fd;
	char	**buff;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		cub3d_err(data, "Failed opening file\n");
	nbr_lines = get_nbr_lines(fd);
	buff = malloc(sizeof(char *) * (nbr_lines + 1));
	if (!buff)
		cub3d_err(data, "Malloc error\n");
	buff[nbr_lines] = NULL;
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (free_array((void **)buff),
			cub3d_err(data, "Failed opening file\n"), NULL);
	fill_buffer(data, buff, nbr_lines, fd);
	close(fd);
	return (buff);
}

void	check_empty_line(t_data *data)
{
	int	x;

	x = data->map_index -1;
	while (data->tmp_map[++x])
		if (ft_strlen(data->tmp_map[x]) == 0)
			cub3d_err(data, "Empty line after map content\n");
}

t_data	parsing(char *path_map)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	data.floor = -1;
	data.ceiling = -1;
	if (check_file_name(path_map))
		cub3d_err(&data, "file given is not .cub type\n");
	data.tmp_map = parse_file(&data, path_map);
	add_map(&data);
	data.mlx = mlx_init();
	if (!data.mlx)
		mlx_err(&data);
	add_textures_and_colors(&data);
	check_texture_color_error(&data);
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "CUB3D");
	if (!data.win)
		mlx_err(&data);
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	if (!data.img)
		cub3d_err(&data, "mlx_new_image failed\n");
	return (data);
}
