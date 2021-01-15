/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 21:51:12 by dda-silv          #+#    #+#             */
/*   Updated: 2021/01/15 23:06:22 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#define MAX_LINE 1025

int get_next_line(int fd, char **line)
{
	char	buf[BUFFER_SIZE];
	int		i;

	// free(line);
	if (!(*line = malloc(MAX_LINE * sizeof(char))))
		return (-1);
	i = 0;
	while (read(fd, buf, 1))
	{
		if (i == 0 && *buf == '\n')
			continue ;
		if (*buf == '\n')
			return (1);
		(*line)[i] = *buf;
		i++;
		// printf("%c", *buf);
	}
	return (0);
}
