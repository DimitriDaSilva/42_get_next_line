/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 21:51:12 by dda-silv          #+#    #+#             */
/*   Updated: 2021/01/16 14:58:15 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#define MAX_LINE 8192 

int get_next_line(int fd, char **line)
{
	// char		buf[BUFFER_SIZE];
	char		*buf;
	int			i;
	static char	*tmp_line;

	if (!(buf = malloc(BUFFER_SIZE * sizeof(char))))
		return (-1);
	add(1, 1);
	// printf("FD = %d\n", fd);
	// printf("read(fd, 0, 0) = %ld\n", read(fd, 0, 0));
	if (read(fd, 0, 0) == -1)
		return (-1);
	if (line == 0 || fd < 0)
		return (-1);
	// if (tmp_line == *line)
	// 	free(tmp_line);
	if (!(tmp_line = malloc(MAX_LINE * sizeof(char))))
		return (-1);
	i = 0;
	while (read(fd, buf, 1))
	{
		if (*buf == '\n')
		{
			tmp_line[i] = '\0';
			*line = tmp_line;
			free(buf);
			return (1);
		}
		tmp_line[i] = *buf;
		i++;
	}
	// i++;
	tmp_line[i] = '\0';
	*line = tmp_line;
	free(buf);
	// printf("Here at end of get_next_line");
	// free(tmp_line);
	return (0);
}
