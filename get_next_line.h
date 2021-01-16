/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 21:52:42 by dda-silv          #+#    #+#             */
/*   Updated: 2021/01/16 11:22:04 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// To delete
# include <stdio.h>
# include <fcntl.h>

// To keep
# include <stdlib.h>
# include <unistd.h>

int		get_next_line(int fd, char **line);
void	add(int nb1, int nb2);

#endif