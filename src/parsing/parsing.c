/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:34:07 by mpignet           #+#    #+#             */
/*   Updated: 2023/02/03 16:08:23 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_data *data)
{
	data = ft_calloc(sizeof(t_data), 1);
	if (!data)
		cub3d_err(data, "malloc error\n");
}

void	fill_line(t_data *data, char *line, int len, int x)
{
	int	i;

	i = 0;
	while (i < len)
	{
		data->map[x][i] = line[i];
		i++;
	}
	data->map[x][i] = '\0';
	return ;
}

mlx_image_t *texture_to_img(t_data *data, char *file)
{
	mlx_image_t		*img;
	mlx_texture_t	*texture;

	texture = mlx_load_png(file);
	if (!texture)
        mlx_err(data);
	img = mlx_texture_to_image(data->mlx, texture);
	if (!img)
        mlx_err(data);
	return (img);
}

char	**parse_file(t_data *data, char *path_file)
{
	int		fd;

	fd = open(path_file, O_RDONLY);
	if (fd == -1)
		cub3d_err(data, "Failed opening file\n");
	//line = get_next_line(fd);
	return (NULL);
}

/* t_data	*add_components(t_data *data, char **map_buff)
{
	char	*line;
	int		len;
	int		x;
	char	**tmp;

	x = 0;
	while (line)
	{
		if (!line)
			continue;
		tmp = ft_split(line, " ");
		if (!tmp)
			exit(42);
		if (!ft_strcmp(tmp[0], "F"))
			;
		if (!ft_strcmp(tmp[0], "C"))
			;
		if (!ft_strcmp(tmp[0], "NO"))
			data->nord = texture_to_img(data, tmp[1]);
		if (!ft_strcmp(tmp[0], "SO"))
			data->south = texture_to_img(data, tmp[1]);
		if (!ft_strcmp(tmp[0], "WE"))
			data->west = texture_to_img(data, tmp[1]);
		if (!ft_strcmp(tmp[0], "EA"))
			data->east = texture_to_img(data, tmp[1]);
		free(line);
		line = get_next_line(fd);
	}
	line = get_next_line(fd);
	while (line)
	{
		len = 0;
		while (line[len] && line[len] != '\n')
			len++;
		data->map[x] = malloc(sizeof(char) * (len + 1));
		if (!data->map[x])
			return (close(fd), 1);
		fill_line(data, line, len, x);
		free(line);
		line = get_next_line(fd);
		x++;
	}
	data->map[x] = NULL;
	return (close(fd), 0);
	return (data);
} */

t_data	*parsing(char *path_map)
{
	t_data	data;
	char	**map_buff;

	init_data(&data);
	if (check_file_name(path_map))
		cub3d_err(&data, "file given is not .cub type\n");
	map_buff = parse_file(&data, path_map);
	data.mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (!data.mlx)
		mlx_err(&data);
	(void)map_buff;
	//add_components(&data, map_buff);
	return (NULL);
}