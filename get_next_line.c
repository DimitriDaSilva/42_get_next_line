/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 21:51:12 by dda-silv          #+#    #+#             */
/*   Updated: 2021/02/13 12:33:37 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	static t_trackers	trackers;
	t_tracker			*tracker;
	int					i;
	char				*line_feed;

	if (read(fd, 0, 0) == -1)
		return (-1);
	tracker = get_tracker(fd, &trackers);
	*line = malloc(MAX_LINE);
	if (!(*line))
		return (-1);
	i = 0;
	while (read(fd, tracker->buf, BUFFER_SIZE))
	{
		line_feed = ft_strchr(tracker->buf, '\n');
		if (line_feed != 0)
		{
			ft_memcpy(*(line + i), tracker->buf, line_feed - tracker->buf);
			(*line)[i + line_feed - tracker->buf] = '\0';
			ft_memcpy(tracker->buf, line_feed + 1, BUFFER_SIZE - (line_feed - tracker->buf) - 1);
			tracker->buf[(int)(BUFFER_SIZE - (line_feed - tracker->buf) - 1)] = '\0';
			return (1);
		}
		else
			ft_memcpy(*(line + i), tracker->buf, BUFFER_SIZE);
		i += BUFFER_SIZE;
	}
	return (0);
	// if (!(buf = malloc(BUFFER_SIZE)))
	// 	return (-1);
	// if (!(*line = malloc(MAX_LINE)))
	// 	return (-1);
	// i = 0;
	// while (read(fd, buf, 1))
	// {
	// 	if (*buf == '\n')
	// 	{
	// 		(*line)[i] = '\0';
	// 		free(buf);
	// 		return (1);
	// 	}
	// 	(*line)[i++] = *buf;
	// }
	// (*line)[i] = '\0';
	// free(buf);
	// return (0);
}
