/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:40:42 by mpignet           #+#    #+#             */
/*   Updated: 2023/02/05 16:47:11 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_map_len(t_data *data)
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

static void	set_player_dir(t_data *data, char dir)
{
	if (dir == 'N')
	{
		data->dir_x = -1;
		data->dir_y = 0;
	}
	else if (dir == 'S')
	{
		data->dir_x = 0;
		data->dir_y = 0;
	}
	else if (dir == 'W')
	{
		data->dir_x = 0;
		data->dir_y = 1;			
	}
	else if (dir == 'E')
	{
		data->dir_x = 0;
		data->dir_y = -1;
	}
}

static void	set_player_start_pos(t_data *data, int i, int k, int j)
{
	data->map[k][j] = 0;
	data->pos_y = (double)k;
	data->pos_x = (double)j;
	if (data->tmp_map[i][j] == 'N')
		set_player_dir(data, 'N');
	else if (data->tmp_map[i][j] == 'S')
		set_player_dir(data, 'S');
	else if (data->tmp_map[i][j] == 'W')
		set_player_dir(data, 'W');
	else if (data->tmp_map[i][j] == 'E')
		set_player_dir(data, 'E');
}

static void	set_box_infos(t_data *data, int i, int j, int k)
{
	if (data->tmp_map[i][j] == 'N' || data->tmp_map[i][j] == 'S'
		|| data->tmp_map[i][j] == 'W' || data->tmp_map[i][j] == 'E')
		set_player_start_pos(data, i, k, j);
	else if (data->tmp_map[i][j] == ' ')
		data->map[k][j] = SPACE;
	else
		data->map[k][j] = data->tmp_map[i][j] - 48;	
}

void	add_map(t_data *data)
{
	int		i;
	int		j;
	int		k;
	int		len;

	i = 0;
	k = 0;
	data->map = malloc(sizeof(int *) * (get_map_len(data) + 1));
	if (!data->map)
		cub3d_err(data, "Malloc error\n");
	while (i < data->map_index)
		i++;
	while (data->tmp_map[i])
	{
		j = -1;
		len = ft_strlen(data->tmp_map[i]);
		data->map[k] = malloc(sizeof(int) * (len + 1));
		data->map[k][len] = END;
		while(data->tmp_map[i][++j])
			set_box_infos(data, i, j ,k);
		i++;
		k++;
	}
	data->map[k] = malloc(sizeof(int));
	data->map[k][0] = END;
	// i = -1;
	// while(data->map[++i][0] != END)
	// {
	// 	j = -1;
	// 	printf("data->map[%d] : ", i);
	// 	while(data->map[i][++j] != END)
	// 		printf("%d", data->map[i][j]);
	// 	printf("\n");
	// }
}