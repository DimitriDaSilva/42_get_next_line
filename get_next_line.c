/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dds <dda-silv@student.42lisboa.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 21:51:12 by dda-silv          #+#    #+#             */
/*   Updated: 2021/02/14 11:23:43 by dds              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** Gets the next line in a open file or stdin. Called in a loop. The line
** passed as an argument gets freed by the caller, NOT get_next_line()
** @param:	- [int] open file or stdin
**			- [char **] dest of the line
** @return:	[int] 1 new line is found, 0 EOF reached, -1 error occurred
** Line-by-line comments:
** @1		The static struct t_buffers has the number of active buffers and
**			array of t_buffer. Only gets init the first time it's called
** @2		Buffer that will get used for this fd. As two variables, fd and *buf
** @5-6		Edge case: fd not valid or dest string is NULL
** @7		Gets the proper buffer (i.e. a new one or an old one if the fd has
**			previously been passed)
** @8-11	The line dest allocated space gets freed by the caller function
** @13		It loops until:
**			- the buffer has been emptied. Case where there is a leftover from
**			another call of GNL
**			- the EOF has not been reached
**			There is a read only if the buf is empty
** @15-16	Cases: line feed or EOF has been found in the buffer read.
**			get_rest_line() returns 1 if \n and 0 if EOF. If also copies
**			the piece of the buf into the line while moving the leftover
**			buf from the right to the left
** @18		Index of the dest line
** @19		Erases the buf otherwise the first while condition still is true
*/

int			get_next_line(int fd, char **line)
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

/*
** Gets the proper buffer, either a new one or an old one if fd is known. It
** tries to find the buffer in the array, if it doesn't it means it needs to
** create a new one
** @param:	- [int] fd to read from
**			- [t_buffers] struct with number of active buffers and array
**                        of t_buffer (int fd and char *buf)
** @return:	[t_buffer *] correct buffer (old one or new one)
** Line-by-line comments:
** @1-5		Case: GNL has already been called for this fd and a buffer has
**			already been created, in which case we return it
** @7-9		It's the first buffer created in the array. We malloc for 
*/

t_buffer	*get_buffer(int fd, t_buffers *buffers)
{
	int	buffer_index;

	buffer_index = find_buffer(fd, buffers->arr);
	if (buffer_index != -1)
		return (&buffers->arr[buffer_index]);
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

int			get_rest_line(char *line, t_buffer *buffer, t_buffers *buffers)
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
	if (*(ptr_eol + 1) == 0)
		ft_memset(buffer->buf, 0, BUFFER_SIZE + 1);
	else
		ft_memcpy(buffer->buf, ptr_eol + 1, BUFFER_SIZE - rest_size);
	if (ret == 0)
		free_buffers(buffers, buffer);
	return (ret);
}

void		free_buffers(t_buffers *buffers, t_buffer *buffer)
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
