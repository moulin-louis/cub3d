/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:34:07 by mpignet           #+#    #+#             */
/*   Updated: 2023/02/06 14:38:23 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_image_t	*texture_to_img(t_data *data, char **tmp)
{
	mlx_image_t		*img;
	mlx_texture_t	*texture;

	texture = mlx_load_png(tmp[1]);
	if (!texture)
		return (free_array((void **)tmp), mlx_err(data), NULL);
	img = mlx_texture_to_image(data->mlx, texture);
	if (!img)
		return (mlx_delete_texture(texture), free_array((void **)tmp),
			mlx_err(data), NULL);
	return (mlx_delete_texture(texture), img);
}

void	add_textures(t_data *data)
{
	int		i;
	char	**tmp;

	i = -1;
	while (data->tmp_map[++i])
	{
		if (data->tmp_map[i] == NULL)
			continue ;
		tmp = ft_split(data->tmp_map[i], ' ');
		if (!tmp)
			cub3d_err(data, "Malloc error\n");
		if (!ft_strcmp(tmp[0], "NO"))
			data->nord = texture_to_img(data, tmp);
		else if (!ft_strcmp(tmp[0], "SO"))
			data->south = texture_to_img(data, tmp);
		else if (!ft_strcmp(tmp[0], "WE"))
			data->west = texture_to_img(data, tmp);
		else if (!ft_strcmp(tmp[0], "EA"))
			data->east = texture_to_img(data, tmp);
		else if (!ft_strcmp(tmp[0], "F"))
			data->floor = get_color(data, tmp);
		else if (!ft_strcmp(tmp[0], "C"))
			data->ceiling = get_color(data, tmp);
		free_array((void **)tmp);
	}
}

char	**fill_buffer(t_data *data, char **buff, int nbr_lines, int fd)
{
	int		i;
	char	*tmp;

	i = -1;
	while (++i < nbr_lines)
	{
		buff[i] = get_next_line(fd);
		tmp = buff[i];
		buff[i] = ft_strtrim(buff[i], "\n");
		if (!buff[i])
			return (free(tmp), free_array((void **)buff),
				cub3d_err(data, "Failed opening file\n"), NULL);
		free(tmp);
	}
}

char	**parse_file(t_data *data, char *file)
{
	int		nbr_lines;
	int		fd;
	char	**buff;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		cub3d_err(data, "Failed opening file\n");
	nbr_lines = get_nbr_lines(fd);
	buff = malloc(sizeof(char *) * (nbr_lines + 1));
	buff[nbr_lines] = NULL;
	if (!buff)
		cub3d_err(data, "Malloc error\n");
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (free_array((void **)buff),
			cub3d_err(data, "Failed opening file\n"), NULL);
	fill_buffer(data, buff, nbr_lines, fd);
	return (buff);
}

t_data	parsing(char *path_map)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	if (check_file_name(path_map))
		cub3d_err(&data, "file given is not .cub type\n");
	data.tmp_map = parse_file(&data, path_map);
	add_map(&data);
	data.mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (!data.mlx)
		mlx_err(&data);
	add_textures(&data);
	return (data);
}
