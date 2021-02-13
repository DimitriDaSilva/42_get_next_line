/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 21:51:12 by dda-silv          #+#    #+#             */
/*   Updated: 2021/02/13 23:34:38 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	static t_buffers	buffers = { 0, 0 };
	t_buffer			*buffer;
	int					i;

	if (read(fd, 0, 0) == -1 || !line)
		return (-1);
	buffer = get_buffer(fd, &buffers);
	*line = malloc(MAX_LINE);
	if (!(*line))
		return (-1);
	ft_memset(*line, 0, MAX_LINE);
	i = 0;
	while (*buffer->buf != 0 || read(fd, buffer->buf, BUFFER_SIZE))
	{
		if (ft_strchr(buffer->buf, '\n') || ft_strchr(buffer->buf, EOF_CHAR))
			return (get_rest_line(*(line) + i, buffer, &buffers));
		ft_memcpy(&(*line)[i], buffer->buf, ft_strlen(buffer->buf));
		i += ft_strlen(buffer->buf);
		ft_memset(buffer->buf, 0, BUFFER_SIZE);
	}
	return (0);
}

t_buffer	*get_buffer(int fd, t_buffers *buffers)
{
	if (find_buffer(fd, buffers->arr) == -1)
	{
		buffers->len++;
		if (buffers->len == 1)
			buffers->arr = malloc((buffers->len + 1) * sizeof(t_buffer));
		else
			buffers->arr = ft_realloc(buffers->arr,
										buffers->len * sizeof(t_buffer),
										(buffers->len + 1) * sizeof(t_buffer));
		if (!buffers->arr)
			return (0);
		buffers->arr[buffers->len - 1].fd = fd;
		buffers->arr[buffers->len - 1].buf = malloc(BUFFER_SIZE + 1);
		if (!buffers->arr[buffers->len - 1].buf)
			return (0);
		ft_memset(buffers->arr[buffers->len - 1].buf, 0, BUFFER_SIZE + 1);
		buffers->arr[buffers->len] = (t_buffer){ -1, 0 };
		return (&buffers->arr[buffers->len - 1]);
	}
	else
		return (&buffers->arr[find_buffer(fd, buffers->arr)]);
}

int			find_buffer(int fd, t_buffer *arr)
{
	int	buffer_index;
	int	i;

	buffer_index = -1;
	if (arr == 0)
		return (buffer_index);
	i = -1;
	while (arr[++i].buf)
	{
		if (arr[i].fd == fd)
		{
			buffer_index = i;
			break ;
		}
	}
	return (buffer_index);
}

int		get_rest_line(char *line, t_buffer *buffer, t_buffers *buffers)
{
	char	*ptr_eol;
	int		rest_size;
	int		ret;

	ptr_eol = ft_strchr(buffer->buf, '\n');
	if (!ptr_eol)
	{
		ptr_eol = ft_strchr(buffer->buf, EOF_CHAR);
		ret = 0;
	}
	else 
		ret = 1;
	rest_size = ptr_eol - buffer->buf;
	ft_memcpy(line, buffer->buf, rest_size);
	line[rest_size] = 0;
	ft_memcpy(buffer->buf, ptr_eol + 1, BUFFER_SIZE - rest_size);
	if (ret == 0)
		free_buffers(buffers, buffer);
	return (ret);
}
		// if (ft_strchr(buffer->buf, '\n'))
		// {
		// 	get_rest_line(*(line) + i, buffer->buf, '\n');
		// 	return (1);
		// }
		// else if (ft_strchr(buffer->buf, EOF_CHAR))
		// {
		// 	get_rest_line(*(line) + i, buffer->buf, EOF_CHAR);
		// }

void	free_buffers(t_buffers *buffers, t_buffer *buffer)
{
	int	was_last_buffer;
	int	i;

	was_last_buffer = 1;
	free(buffer->buf);
	buffer->fd = -1;
	i = -1;
	while (++i < buffers->len)
	{
		if (buffers->arr[i].fd != -1)
			was_last_buffer = 0;
	}
	if (was_last_buffer)
		free(buffers->arr);
}
