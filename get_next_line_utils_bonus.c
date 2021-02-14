/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dds <dda-silv@student.42lisboa.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 08:57:21 by dda-silv          #+#    #+#             */
/*   Updated: 2021/02/14 11:49:44 by dds              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

/*
** Modified ft_strlen so that the count also stops at EOF
** @param:	- [const char *] string to check size
** @return:	[size_t] size of the string without NULL-terminator
*/

size_t	ft_strlen(const char *s)
{
	size_t count;

	count = 0;
	while (s[count] != '\0' && s[count] != EOF_CHAR)
		count++;
	return (count);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*sav_s;

	sav_s = s;
	while (n--)
		*sav_s++ = c;
	return (s);
}
