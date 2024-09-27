/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:13:05 by silndoj           #+#    #+#             */
/*   Updated: 2024/09/27 15:12:58 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		mini.arguments = allocate_command(mini.line, &mini, 0);
//		print_arguments(mini.arguments);
		 if (mini.argc > 0)
		 {
		 	execute(&mini);
		 	free_stuff(&mini);
		 }
		unlink("here_doc.txt");
	}
}
