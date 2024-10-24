/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 04:08:13 by silndoj           #+#    #+#             */
/*   Updated: 2024/04/21 19:15:45 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <fcntl.h>
# include <stdio.h>

char	*get_next_line(int fd);
char	*ft_calloc0(size_t count, size_t size);
char	*ft_strchr0(const char *s, int c);
size_t	ft_strlen0(const char *str);
char	*ft_strjoin0(char const *s1, char const *s2);
void	*ft_memcpy0(void *dest, const void *src, size_t n);

#endif
