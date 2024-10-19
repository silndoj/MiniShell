/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:11:37 by silndoj           #+#    #+#             */
/*   Updated: 2024/10/18 16:23:48 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error(const char *source)
{
	perror(source);
	_exit(EXIT_FAILURE);
}

static void	pull_back(char **arguments)
{
	size_t	i;

	i = 0;
	free(arguments[i]);
	while (arguments[i])
	{
		arguments[i] = arguments[i + 1];
		i++;
	}
}

void	erase_from(char **strings, size_t count)
{
	size_t	i;

	i = 0;
	while (*strings && i++ < count)
		pull_back(strings);
}
