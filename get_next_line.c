/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dds <dda-silv@student.42lisboa.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 21:51:12 by dda-silv          #+#    #+#             */
/*   Updated: 2021/02/17 10:17:49 by dds              ###   ########.fr       */
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
		ft_memset(buffer->buf, 0, BUFFER_SIZE + 1);
	}
	free_buffers(&buffers, buffer);
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
** @6-7		It's the first buffer created in the array
** @8-11	Not the first buffer created. We add a new one
*/

t_buffer	*get_buffer(int fd, t_buffers *buffers)
{
	int	buffer_index;

	buffer_index = find_buffer(fd, buffers);
	if (buffer_index != -1)
		return (&buffers->arr[buffer_index]);
	if (buffers->len == 0)
		buffers->arr = malloc(sizeof(t_buffer));
	else
		buffers->arr = ft_realloc(buffers->arr,
									buffers->len * sizeof(t_buffer),
									(buffers->len + 1) * sizeof(t_buffer));
	if (!buffers->arr)
		return (0);
	buffers->len++;
	buffers->arr[buffers->len - 1].fd = fd;
	buffers->arr[buffers->len - 1].buf = malloc(BUFFER_SIZE + 1);
	if (!buffers->arr[buffers->len - 1].buf)
		return (0);
	ft_memset(buffers->arr[buffers->len - 1].buf, 0, BUFFER_SIZE + 1);
	return (&buffers->arr[buffers->len - 1]);
}

/*
** Parses the array of buffers and tried to find the current fd in the old
** buffers
** @param:	- [int] fd of the open file or stdin
**			- [t_buffers *] buffers struct with length and array of buffer
** @return:	[int] If buffer found, returns its index. Else -1
*/

int			find_buffer(int fd, t_buffers *buffers)
{
	int	i;

	i = -1;
	while (++i < buffers->len)
	{
		if (buffers->arr[i].fd == fd)
			return (i);
	}
	return (-1);
}

/*
** Functions called when a line feed or EOF has been found in the string read.
** The function copies the characters until line_feed or EOF to the dest line
** @param:	- [char *] destination line
**			- [t_buffer *] current buffer
**			- [t_buffers *] buffers struct with length and array of buffer.
**						    Passed here to be freed when relevant
** @return:	[int] 1 if \n found, 0 if EOF found
** Line-by-line comments:
** @6-10	No line feed has been found so we know for sure that a EOF is
**			in the buf somewhere. We want its position
** @13		The size of the string to copy is between begin and where line
**			feed or EOF has been found
** @16-17	If the character after line feed or EOF is a NULL-terminator, we
**			need to clean the buffer
** @18-19	Else we move the buffer for right to the left
** @20-21	If EOF is reached we can free_buffers. At least free(buffer->buf)
*/

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

/*
** Frees buffer->buf and frees buffers->arr if the buffer was the last active
** @param:	- [t_buffers *] buffers struct with length and array of buffer.
**			- [t_buffer *] current buffer
** Line-by-line comments:
** @8-12	If no fd other than -1 is found then no buffer active is left
*/

void		free_buffers(t_buffers *buffers, t_buffer *buffer)
{
	int	was_last_buffer;
	int	i;

	was_last_buffer = 1;
	if (buffer->fd != -1)
	{
		free(buffer->buf);
		buffer->fd = -1;
	}
	i = -1;
	while (++i < buffers->len)
	{
		if (buffers->arr[i].fd != -1)
			was_last_buffer = 0;
	}
	if (was_last_buffer)
	{
		free(buffers->arr);
		buffers->arr = 0;
		buffers->len = 0;
	}
}
