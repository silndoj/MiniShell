/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_uint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:13:10 by silndoj           #+#    #+#             */
/*   Updated: 2024/10/24 16:45:45 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_unsigned_int(unsigned int i, int *count)
{
	if (i >= 10)
		ft_unsigned_int(i / 10, count);
	ft_putchar_count(i % 10 + '0', count);
	count++;
}
