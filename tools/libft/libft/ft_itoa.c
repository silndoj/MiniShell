/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:22:25 by silndoj           #+#    #+#             */
/*   Updated: 2024/10/24 19:19:57 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	int_len(int n)
{
	int		i;
	long	len;

	i = 1;
	len = n;
	if (len < 0)
	{
		len *= (-1);
		i++;
	}
	while (len >= 10)
	{
		len /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*nbr;
	long	len;
	int		slen;

	len = n;
	slen = int_len(n);
	nbr = ft_calloc(slen + 1, sizeof(char));
	if (!nbr)
		return (NULL);
	if (len == 0)
	{
		nbr[0] = '0';
		return (nbr);
	}
	if (len < 0)
	{
		nbr[0] = '-';
		len = -len;
	}
	while (len > 0)
	{
		nbr[--slen] = (len % 10) + '0';
		len /= 10;
	}
	return (nbr);
}
