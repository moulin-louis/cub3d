/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:34:07 by mpignet           #+#    #+#             */
/*   Updated: 2023/02/05 16:52:52 by loumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_image_t *texture_to_img(t_data *data, char **tmp)
{
	mlx_image_t		*img;
	mlx_texture_t	*texture;

	texture = mlx_load_png(tmp[1]);
	if (!texture)
        return (free_array((void **)tmp), mlx_err(data), NULL);
	img = mlx_texture_to_image(data->mlx, texture);
	if (!img)
        return (free_array((void **)tmp), mlx_err(data), NULL);
	return (img);
}

char	**parse_file(t_data *data, char *file)
{
	int		i;
	int		nbr_lines;
	int		fd;
	char	**buff;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		cub3d_err(data, "Failed opening file\n");
	i = -1;
	nbr_lines = get_nbr_lines(fd);
	buff = malloc(sizeof(char *) * (nbr_lines + 1));
	if (!buff)
		cub3d_err(data, "Malloc error\n");
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (free_array((void **)buff),
			cub3d_err(data, "Failed opening file\n"), NULL);
	while (++i < nbr_lines)
	{
		buff[i] = get_next_line(fd);
		buff[i] = ft_strtrim(buff[i], "\n");
	}
	//buff[i] = NULL;
	return (buff);
}

int	get_color(t_data *data, char **tmp)
{
	int	color;
	char	**buff;

	buff = ft_split(tmp[1], ',');
	if (!buff)
		cub3d_err(data, "Malloc error\n");
	else if (array_len((void **)buff) != 3)
	{
		free_array((void **)tmp);
		free_array((void **)buff);
		cub3d_err(data, "Color description error : format needed: r, g, b\n");
	}
	color = get_rgba(ft_atoi(buff[0]), ft_atoi(buff[1]), ft_atoi(buff[2]), 255);
	return (free_array((void **)buff), color);
}

void	add_textures(t_data *data)
{
	int		i;
	char	**tmp;

	i = -1;
	while (data->tmp_map[++i])
	{
		if (data->tmp_map[i] == NULL)
			continue;
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

int	get_map_len(t_data *data)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while(data->tmp_map && data->tmp_map[i])
	{
		if(data->tmp_map[i] && (data->tmp_map[i][0] == '1' || data->tmp_map[i][0] == ' '))
		{
			data->map_index = i;	
			while(data->tmp_map[i] && (data->tmp_map[i][0] == '1' || data->tmp_map[i][0] == ' '))
			{
				len++;
				i++;
			}
			return(len);
		}
		i++;
	}
	return (len);
}

t_data	parsing(char *path_map)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (check_file_name(path_map))
		cub3d_err(&data, "file given is not .cub type\n");
	data.tmp_map = parse_file(&data, path_map);
	data.mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (!data.mlx)
		mlx_err(&data);
	add_textures(&data);
	add_map(&data);
	return (data);
}