/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:49:44 by loumouli          #+#    #+#             */
/*   Updated: 2023/02/16 17:22:30 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_texture_color_error(t_data *data)
{
	if (!data->nord.img)
		cub3d_err(data, "Missing path for North walls\n");
	if (!data->south.img)
		cub3d_err(data, "Missing path for South walls\n");
	if (!data->west.img)
		cub3d_err(data, "Missing path for West walls\n");
	if (!data->east.img)
		cub3d_err(data, "Missing path for East walls\n");
	if (data->floor == -1)
		cub3d_err(data, "Missing color for Floor\n");
	if (data->ceiling == -1)
		cub3d_err(data, "Missing color for Ceiling\n");
}

void	check_invalid_info(t_data *data, char **tmp)
{
	int	len;

	len = array_len((void **)tmp);
	if (tmp[0])
	{
		if (ft_strcmp(tmp[0], "F") && ft_strcmp(tmp[0], "C")
			&& ft_strcmp(tmp[0], "WE") && ft_strcmp(tmp[0], "EA")
			&& ft_strcmp(tmp[0], "NO") && ft_strcmp(tmp[0], "SO"))
		{
			free_array((void **)tmp);
			cub3d_err(data, "Unknown identifier in file\n");
		}
	}
	if (len != 0 && len != 2)
	{
		free_array((void **)tmp);
		cub3d_err(data, "Color or Texture description : wrong infos\n");
	}
}

int	check_color(char **buff)
{
	unsigned int	result[3];

	if (!ut_atoi(&result[0], buff[0]) || !ut_atoi(&result[1], buff[1])
		|| !ut_atoi(&result[2], buff[2]))
		return (-1);
	if ((result[0] > 255 || result[1] > 255 || result[2] > 255))
		return (-1);
	return (get_rgb(result[0], result[1], result[2]));
}

bool	ut_atoi(unsigned int *nbr, const char *str)
{
	unsigned int	nbr_tmp;
	unsigned int	nbr_tmp2;
	int				i;

	*nbr = 0;
	i = -1;
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (false);
	while (*str && *str >= '0' && *str <= '9')
	{
		i = 0;
		nbr_tmp2 = *nbr;
		while (i++ < 9)
		{
			nbr_tmp = *nbr;
			*nbr += nbr_tmp2;
			if (*nbr < (unsigned int)nbr_tmp)
				return (false);
		}
		*nbr = *nbr + (*str - 48);
		str++;
	}
	return (true);
}

void	free_arr_exit(char **arr, t_data *data, char *err)
{
	free_array((void **)arr);
	cub3d_err(data, err);
}
