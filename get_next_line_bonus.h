/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 08:33:26 by dda-silv          #+#    #+#             */
/*   Updated: 2021/02/13 23:25:52 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# define MAX_LINE 200000
# define EOF_CHAR '\xbe'

typedef struct	s_buffer
{
	int			fd;
	char		*buf;
}				t_buffer;

typedef struct	s_buffers
{
	t_buffer	*arr;
	int			len;
}				t_buffers;

int			get_next_line(int fd, char **line);
t_buffer	*get_buffer(int fd, t_buffers *buffers);
int			find_buffer(int fd, t_buffer *arr);
int			get_rest_line(char *dest, t_buffer *buffer, t_buffers *buffers);
void		free_buffers(t_buffers *buffers, t_buffer *buffer);

void		*ft_realloc(void *ptr, size_t orig_size, size_t new_size);
void		*ft_memcpy(void *dest, const void *src, size_t n);
char		*ft_strchr(const char *s, int c);
size_t		ft_strlen(const char *s);
void		*ft_memset(void *s, int c, size_t n);

#endif
