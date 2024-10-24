/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 20:37:27 by silndoj           #+#    #+#             */
/*   Updated: 2024/10/24 19:32:21 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*flag;

	flag = NULL;
	while (*s)
	{
		if (*s == (char) c)
			flag = (char *) s;
		s++;
	}
	if (*s == (char) c)
		flag = (char *) s;
	if (!(flag == 0))
		return (flag);
	return (0);
}
