/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:01:19 by silndoj           #+#    #+#             */
/*   Updated: 2024/10/24 19:30:54 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*t1;
	size_t	slen;

	slen = ft_strlen(s1);
	t1 = (char *) ft_calloc((slen + 1), sizeof(char));
	if (!t1)
		return (0);
	ft_memcpy(t1, s1, slen);
	return (t1);
}
