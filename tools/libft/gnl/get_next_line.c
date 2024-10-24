/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 03:31:23 by silndoj           #+#    #+#             */
/*   Updated: 2024/10/24 19:33:16 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*ft_strdup0(const char *s1, int count)
{
	char	*t1;
	size_t	slen;

	slen = ft_strlen0(s1);
	t1 = (char *) ft_calloc0((slen + 1), sizeof(char));
	if (!t1)
		return (NULL);
	ft_memcpy0(t1, s1, count + 1);
	return (t1);
}

char	*read_again(int fd, char *block)
{
	char	*block_temp;
	int		read_bytes;
	char	*temp;

	read_bytes = 0;
	while (!ft_strchr0(block, '\n'))
	{
		block_temp = ft_calloc0((BUFFER_SIZE + 1), sizeof(char));
		if (!block_temp)
			return (free(block), NULL);
		read_bytes = read(fd, block_temp, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free(block_temp), free(block), NULL);
		if (!read_bytes)
		{
			free(block_temp);
			break ;
		}
		block_temp[read_bytes] = 0;
		temp = ft_strjoin0(block, block_temp);
		free(block);
		block = temp;
		free(block_temp);
	}
	return (block);
}

char	*nextblock_reset(char *block, int *count)
{
	int		i;
	char	*line;

	i = 0;
	while (block[i] != '\0' && block[i] != '\n')
		i++;
	*count = i;
	line = ft_strdup0(block, i);
	if (!line)
		return (free(block), NULL);
	return (line);
}

char	*ft_substr0(char const *s, unsigned int start, size_t len)
{
	size_t	slen;
	size_t	sublen;
	char	*ptr;

	if (!s)
		return (NULL);
	slen = ft_strlen0(s);
	sublen = slen - start;
	if (sublen > len)
		sublen = len;
	ptr = (char *) ft_calloc0((sublen + 1), sizeof(char));
	if (!ptr)
		return (NULL);
	ft_memcpy0(ptr, (s + start + 1), sublen);
	ptr[sublen] = 0;
	return (ptr);
}

char	*get_next_line(int fd)
{
	static char	*block;
	char		*nextblock;
	char		*tmpblock;
	int			count;

	count = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!block)
	{
		block = ft_calloc0(1, 1);
		if (!block)
			return (NULL);
	}
	block = read_again(fd, block);
	if (!block)
		return (NULL);
	nextblock = nextblock_reset(block, &count);
	if (!nextblock)
		return (free(block), block = NULL, NULL);
	if (ft_strlen0(nextblock) == 0)
		return (free(block), free(nextblock), block = NULL, NULL);
	tmpblock = ft_substr0(block, count, (ft_strlen0(block) - count));
	free(block);
	return (block = tmpblock, nextblock);
}
