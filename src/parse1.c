/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:30:08 by silndoj           #+#    #+#             */
/*   Updated: 2024/10/18 20:29:32 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

static size_t	count_(char **strings)
{
	size_t	count;

	count = 0;
	while (strings[count])
		count++;
	return (count);
}

static void	skip_delimiters(char const *s, char d, size_t *current)
{
	while (s[*current] && s[*current] == d)
		(*current)++;
}

static size_t	word_length(char const *s, char d, size_t *current)
{
	size_t	length;

	length = 0;
	while (s[*current] && (s[(*current)++] != d || !d))
		length++;
	return (length);
}

char	***parse(char *line)
{
	char			***commands;
	char			**splitted;
	size_t			count;

	splitted = ft_split(line, '|');
	count = count_(splitted);
	g_pipe_count = count - 1;
	commands = malloc(sizeof(char **) * (count + 1));
	commands[count] = NULL;
	while (count-- > 0)
		commands[count] = ft_split(splitted[count], ' ');
	free_2dchar(splitted);
	free(line);
	//print_arguments(*commands);
	return (commands);
}
