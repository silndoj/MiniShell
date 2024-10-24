/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:07:23 by silndoj           #+#    #+#             */
/*   Updated: 2024/10/20 03:35:32 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	next_redirect_out(char ***arguments)
{
	while (**arguments)
	{
		if (!ft_strncmp(**arguments, ">", 2)
			|| !ft_strncmp(**arguments, ">>", 3))
			return (true);
		(*arguments)++;
	}
	return (false);
}

static void	redirect_out_to(const char *filename, int option)
{
	static int	output;

	if (output)
		close(output);
	if (option == TRUNCATE)
		output = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		output = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (output == ERROR)
		exit_error("open");
	dup2(output, STDOUT_FILENO);
	close(output);
}

bool	redirect_out(char **arguments)
{
	char	*filename;

	while (next_redirect_out(&arguments))
	{
		filename = strdup(arguments[1]);
		if (!ft_strncmp(arguments[0], ">", 2))
			redirect_out_to(filename, TRUNCATE);
		else if (!ft_strncmp(arguments[0], ">>", 3))
			redirect_out_to(filename, APPEND);
		erase_from(arguments, 2);
		free(filename);
	}
	return (true);
}
