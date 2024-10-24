/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:46:18 by silndoj           #+#    #+#             */
/*   Updated: 2024/10/24 19:31:15 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	s1len;
	size_t	s2len;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	ptr = (char *) ft_calloc((s1len + s2len + 1), sizeof(char));
	if (!ptr)
		return (0);
	ft_memcpy(ptr, s1, s1len);
	ft_memcpy((ptr + s1len), s2, s2len);
	return (ptr);
}
