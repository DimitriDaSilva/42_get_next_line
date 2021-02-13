/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 09:15:52 by dda-silv          #+#    #+#             */
/*   Updated: 2021/02/13 12:45:32 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_realloc(void *ptr, size_t orig_size, size_t new_size)
{
	void	*new_ptr;

	new_ptr = 0;
	if (new_size == 0)
		free(ptr);
	else if (!ptr)
	{
		if (!(new_ptr = malloc(new_size)))
			return (0);
	}
	else if (new_size <= orig_size)
		return (ptr);
	else if (ptr && new_size > orig_size)
	{
		if (!(new_ptr = malloc(new_size)))
			return (0);
		ft_memcpy(new_ptr, ptr, orig_size);
		free(ptr);
	}
	return (new_ptr);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	void	*sav_dest;

	sav_dest = dest;
	while (n-- && dest != src)
		*(char *)sav_dest++ = *(char *)src++;
	return (dest);
}


t_tracker	*get_tracker(int fd, t_trackers *trackers)
{
	trackers->len = count_trackers(trackers->arr);
	if (trackers->len == 0)
	{
		trackers->arr = malloc(2 * sizeof(t_tracker));
		if (!trackers->arr)
			return (0);
		trackers->arr[0].fd = fd;
		trackers->arr[0].buf = malloc(BUFFER_SIZE * sizeof(char));
		if (!trackers->arr[0].buf)
			return (0);
		trackers->arr[1] = (t_tracker){ -1, 0 };
		return (&trackers->arr[0]);
	}
	else if (is_fd_new(fd, trackers->arr))
	{
		trackers->arr = ft_realloc(trackers->arr,
							(trackers->len + 1) * sizeof(t_tracker),
							(trackers->len + 2) * sizeof(t_tracker));
		if (!trackers->arr)
			return (0);
		trackers->arr[trackers->len + 1].fd = fd;
		trackers->arr[trackers->len + 1].buf = malloc(BUFFER_SIZE * sizeof(char));
		if (!trackers->arr[trackers->len + 1].buf)
			return (0);
		trackers->arr[trackers->len + 2] = (t_tracker){ -1, 0 };
		return (&trackers->arr[trackers->len + 1]);
	}
	else
		return (&trackers->arr[find_tracker(fd, trackers->arr)]);
}

int			count_trackers(t_tracker *arr)
{
	int	count;

	count = 0;
	if (!arr)
		return (count);
	while (arr[count].buf)
		count++;
	return (count);
}

int			is_fd_new(int fd, t_tracker *arr)
{
	int	check;
	int	i;

	check = 1;
	i = -1;
	while (arr[++i].buf)
	{
		if (arr[i].fd == fd)
		{
			check = 0;
			break ;
		}
	}
	return (check);
}

int			find_tracker(int fd, t_tracker *arr)
{
	int	i;

	i = -1;
	while (arr[++i].buf)
	{
		if (arr[i].fd == fd)
			break ;
	}
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (c == 0)
		return ((char *)s);
	return (0);
}
