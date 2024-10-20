/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 03:32:11 by silndoj           #+#    #+#             */
/*   Updated: 2024/10/20 03:33:48 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	next_redirect_in(char ***arguments)
{
	while (**arguments)
	{
		if (!ft_strncmp(**arguments, "<", 2))
			return (true);
		(*arguments)++;
	}
	return (false);
}

static void	redirect_in_from(const char *filename)
{
	static int	input;

	if (input)
		close(input);
	input = open(filename, O_RDONLY, 0777);
	if (input == ERROR)
		exit_error("open");
	dup2(input, STDIN_FILENO);
	close(input);
}

bool	redirect_in(char **arguments)
{
	char	*filename;

	while (next_redirect_in(&arguments))
	{
		filename = ft_strdup(arguments[1]);
		if (!filename)
			exit_error("redirect_in");
		redirect_in_from(filename);
		erase_from(arguments, 2);
		free(filename);
	}
	return (true);
}
