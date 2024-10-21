/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:13:05 by silndoj           #+#    #+#             */
/*   Updated: 2024/10/21 03:48:00 by silndoj          ###   ########.fr       */
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

char	*increment(char *string)
{
	char	*number;
	char	*returnstring;
	int		nr;

	number = ft_strchr(string, '=') + 1;
	nr = ft_atoi(number) + 1;
	number = ft_itoa(nr);
	returnstring = ft_strjoin("SHLVL=", number);
	free(number);
	return (returnstring);
}

void	init(t_mini *ministruct, char **envp)
{
	int	i;

	i = 0;
	read_perma_history();
	ministruct->nr_var = 0;
	ministruct->argc = 0;
	while (envp[i] != 0)
		i ++;
	ministruct->envp = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (envp[i] != 0)
	{
		if (ft_strncmp(envp[i], "SHLVL", 5) != 0)
			ministruct->envp[i] = ft_strdup(envp[i]);
		else
			ministruct->envp[i] = increment(envp[i]);
		i ++;
	}
	ministruct->envp[i] = 0;
	realloc_smaller_2d(ministruct, "OLDPWD");
}

void	loop_mini(t_mini mini)
{
	char	mode;

	while (1)
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
