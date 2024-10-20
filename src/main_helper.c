/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:13:05 by silndoj           #+#    #+#             */
/*   Updated: 2024/10/20 17:17:33 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_pipe_count;

static void	run(char ***commands)
{
	static int	i;

	i = -1;
	while (commands[++i])
		if (commands[i])
			execute(commands[i], i);
	while (i-- > 0)
		free_2dchar(commands[i]);
	free(commands);
}

static void	parse_and_run(char *line)
{
	char		***commands;

	commands = parse(line);
	if (commands)
		run(commands);
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
