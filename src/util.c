/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 03:20:02 by silndoj           #+#    #+#             */
/*   Updated: 2024/10/21 03:50:28 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error(const char *source)
{
	perror(source);
	exit(EXIT_FAILURE);
}

void	print_arguments(char **arguments)
{
	int	i;

	i = 0;
	while (arguments[i] != 0)
	{
		printf("%s\n", arguments[i]);
		fflush(stdout);
		i ++;
	}
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == 0)
		return (ft_strdup(s2));
	result = malloc (ft_strlen(s1) + ft_strlen(s2) + 1);
	while (s1[i] != 0)
	{
		result[i] = s1[i];
		i ++;
	}
	while (s2[j] != 0)
	{
		result[i] = s2[j];
		i ++;
		j ++;
	}
	result[i] = 0;
	free(s1);
	return (result);
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
