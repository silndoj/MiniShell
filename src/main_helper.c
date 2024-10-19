/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:13:05 by silndoj           #+#    #+#             */
/*   Updated: 2024/10/18 21:04:22 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_pipe_count;

static void	run(char ***commands, bool backgr)
{
	static int	i;

	i = -1;
	while (commands[++i])
		if (commands[i])
			execute(commands[i], backgr, i);
	while (i-- > 0)
		free_2dchar(commands[i]);
	free(commands);
}

static void	check(char *mode, int count, char **arguments)
{
	if (count == 1)
		*mode = INTERACTIVE;
	else if (count == 3 && !ft_strncmp(arguments[1], "-c", 2))
		*mode = COMMANDLINE;
	else
		exit_error("check");
}

static void	parse_and_run(char *line)
{
	char		***commands;
	static bool	backgr;

	backgr = line[ft_strlen(line) - 1] == '&';
	commands = parse(line);
	if (commands)
		run(commands, backgr);
}

void	loop_mini(t_mini mini)
{
	char	mode;

	while (mini.finished == 0)
	{
		mini.argc = 0;
		mini.exitstatus = WEXITSTATUS(mini.exitcode);
		mini.line = readline("KUHN_SILVESTRI_SHELL % ");
		if (mini.line == 0)
		{
			free_stuff(&mini);
			free_function(&mini);
			exit(0);
		}
		perma_history(mini.line);
		add_history(mini.line);
		parse_and_run(mini.line);
		unlink("here_doc.txt");
	}
}
