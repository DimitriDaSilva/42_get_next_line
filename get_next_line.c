/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 21:51:12 by dda-silv          #+#    #+#             */
/*   Updated: 2021/01/20 17:44:40 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	static char	*buf;
	int			i;

	if (!is_fd_valid(fd))
		return (-1);
	if (!(buf = malloc(BUFFER_SIZE)))
		return (-1);
	if (!(*line = malloc(MAX_LINE)))
		return (-1);
	i = 0;
	while (read(fd, buf, 1))
	{
		if (*buf == '\n')
		{
			(*line)[i] = '\0';
			free(buf);
			return (1);
		}
		(*line)[i++] = *buf;
	}
	(*line)[i] = '\0';
	free(buf);
	return (0);
}
