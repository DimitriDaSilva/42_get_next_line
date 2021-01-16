/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 21:52:42 by dda-silv          #+#    #+#             */
/*   Updated: 2021/01/16 16:04:04 by dda-silv         ###   ########.fr       */
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

# define MAX_LINE 8192 

int		get_next_line(int fd, char **line);
int		is_fd_valid(int fd);

#endif