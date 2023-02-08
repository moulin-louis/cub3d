/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:59:03 by mpignet           #+#    #+#             */
/*   Updated: 2022/10/15 18:29:41 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*fill_line_prep_save(char *buff, char *save)
{
	size_t	i;
	size_t	j;
	char	*line;

	i = 0;
	if (!buff)
		return (NULL);
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i] == '\n')
		i++;
	line = malloc (sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	j = -1;
	while (++j < i && buff[j])
		line[j] = buff[j];
	line[j] = '\0';
	j = 0;
	while (buff[i] && save[j])
		save[j++] = buff[i++];
	save[j] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	save[BUFFER_SIZE + 1];
	char		*buff;
	char		*line;
	ssize_t		ret;

	ret = 1;
	if (BUFFER_SIZE < 1 || fd < 0 || fd > 1024)
		return (NULL);
	buff = NULL;
	buff = ft_strjoin_spec(buff, save);
	while (ret && !ft_strchr_spec(buff, '\n'))
	{
		if (!buff)
			return (NULL);
		ret = read(fd, save, BUFFER_SIZE);
		if (ret == -1)
			return (free(buff), NULL);
		save[ret] = '\0';
		if (!ret && !buff[0])
			return (free(buff), NULL);
		buff = ft_strjoin_spec(buff, save);
	}
	line = fill_line_prep_save(buff, save);
	return (free(buff), line);
}

/* #include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int    main(void)
{
    int    fd;
    char    *result;
    int    i;

    i = 0;
    fd = open("41", O_RDONLY);
    if (fd == -1)
        return (0);
	result = get_next_line(fd);
    printf("RESULT : %s\n", result);
	free(result);
	result = get_next_line(fd);
    printf("RESULT : %s\n", result);
	free(result);
	result = get_next_line(fd);
    printf("RESULT : %s\n", result);
	free(result);
	result = get_next_line(fd);
    printf("RESULT : %s\n", result);
	free(result);
	result = get_next_line(fd);
    printf("RESULT : %s\n", result);
	free(result);
	result = get_next_line(fd);
    printf("RESULT : %s\n", result);
	free(result);
	result = get_next_line(fd);
    printf("RESULT : %s\n", result);
	free(result);
    close(fd);
    return (0);
} */