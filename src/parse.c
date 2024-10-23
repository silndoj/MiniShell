/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 03:19:42 by silndoj           #+#    #+#             */
/*   Updated: 2024/10/23 02:47:10 by silndoj          ###   ########.fr       */
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
//	print_arguments(splitted);
	count = count_s(splitted);
	g_pipe_count = count - 1;
	commands = malloc(sizeof(char **) * (count + 1));
	commands[count] = NULL;
	while (count-- > 0)
		commands[count] = ft_split(splitted[count], ' ');
	free_2dchar(splitted);
	free(line);
	return (commands);
}
