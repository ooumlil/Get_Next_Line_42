/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 03:42:16 by ooumlil           #+#    #+#             */
/*   Updated: 2022/01/13 11:41:52 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	ft_read_fd(int fd, char **nl)
{
	static char	buff[1024][BUFFER_SIZE + 1];
	int			ret;
	size_t		bl;

	if (buff[fd][0] == '\0')
	{
		ret = read(fd, buff[fd], BUFFER_SIZE);
		buff[fd][ret] = '\0';
		if (ret < 1)
		{
			if (ret == -1)
				ft_bzero(*nl, 1);
			return (0);
		}
	}
	bl = 0;
	while (buff[fd][bl] && buff[fd][bl] != '\n')
		bl++;
	if (buff[fd][bl] == '\n')
		bl++;
	*nl = ft_strjoin(*nl, buff[fd]);
	ft_strcpy(buff[fd], &buff[fd][bl]);
	return (1);
}

char	*get_next_line(int fd)
{
	char	*nl;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	nl = malloc (1);
	if (!nl)
		return (NULL);
	nl[0] = '\0';
	while (!ft_strchr(nl, '\n'))
		if (!ft_read_fd(fd, &nl))
			break ;
	if (nl[0] == '\0')
	{
		free(nl);
		return (0);
	}
	return (nl);
}
