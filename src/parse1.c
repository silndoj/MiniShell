/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:30:08 by silndoj           #+#    #+#             */
/*   Updated: 2024/10/20 03:38:56 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_s(char **strings)
{
	size_t	count;

	count = 0;
	while (strings[count])
		count++;
	return (count);
}

char	***parse(char *line)
{
	char			***commands;
	char			**splitted;
	size_t			count;

	splitted = ft_split(line, '|');
	count = count_s(splitted);
	g_pipe_count = count - 1;
	commands = malloc(sizeof(char **) * (count + 1));
	commands[count] = NULL;
	while (count-- > 0)
		commands[count] = ft_split(splitted[count], ' ');
	free_2dchar(splitted);
	free(line);
//	print_arguments(*commands);
	return (commands);
}
