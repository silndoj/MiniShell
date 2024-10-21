/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuhn <kkuhn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 19:32:19 by kkuhn             #+#    #+#             */
/*   Updated: 2024/10/21 03:42:58 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_l)
{
	t_list	*last;

	if (lst == 0 || new_l == 0)
		return ;
	if (*lst == 0)
	{
		*lst = new_l;
		return ;
	}
	last = (*lst);
	while (last->next != 0)
		last = last->next;
	last->next = new_l;
}
