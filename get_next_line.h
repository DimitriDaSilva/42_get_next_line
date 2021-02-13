/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 08:33:26 by dda-silv          #+#    #+#             */
/*   Updated: 2021/02/13 12:44:43 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# define MAX_LINE 200000

typedef struct	s_tracker
{
	int			fd;
	char		*buf;
}				t_tracker;

typedef struct	s_trackers
{
	t_tracker	*arr;
	int			len;
}				t_trackers;

int			get_next_line(int fd, char **line);
void		*ft_realloc(void *ptr, size_t orig_size, size_t new_size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
t_tracker	*get_tracker(int fd, t_trackers *trackers);
int			count_trackers(t_tracker *arr);
int			is_fd_new(int fd, t_tracker *arr);
int			find_tracker(int fd, t_tracker *arr);
char	*ft_strchr(const char *s, int c);

#endif
