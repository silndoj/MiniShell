/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:13:05 by silndoj           #+#    #+#             */
/*   Updated: 2024/10/20 20:26:28 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_pipe_count;

static void	run(t_mini *mini)
{
	static int	i;

	i = -1;
	while (mini->commands[++i])
		if (mini->commands[i])
			execute(mini, i);
	while (i-- > 0)
		free_2dchar(mini->commands[i]);
	free(mini->commands);
}

static void	parse_and_run(t_mini mini)
{
	mini.commands = parse(mini.line);
	if (mini.commands)
		run(&mini);
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
		parse_and_run(mini);
		unlink("here_doc.txt");
	}
}
