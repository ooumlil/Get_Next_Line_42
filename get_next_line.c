/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 08:25:19 by ooumlil           #+#    #+#             */
/*   Updated: 2022/05/10 15:46:57 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_read_fd(int fd, char **line)
{
	static char	buff[BUFFER_SIZE + 1];
	int			ret;
	size_t		len;

	if (buff[0] == '\0')
	{
		ret = read(fd, buff, BUFFER_SIZE);
		buff[ret] = '\0';
		if (ret < 1)
		{
			if (ret == -1)
				ft_bzero(*line, 1);
			return (0);
		}
	}
	len = 0;
	while (buff[len] && buff[len] != '\n')
		len++;
	if (buff[len] == '\n')
		len++;
	*line = ft_strjoin(*line, buff);
	ft_strcpy(buff, &buff[len]);
	return (1);
}

char	*get_next_line(int fd)
{
	char	*line;

	line = malloc(1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	while (!ft_strchr(line, '\n'))
		if (!ft_read_fd(fd, &line))
			break ;
	if (line[0] == '\0')
	{
		free (line);
		return (0);
	}
	return (line);
}
