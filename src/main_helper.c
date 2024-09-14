/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:13:05 by silndoj           #+#    #+#             */
/*   Updated: 2024/09/14 19:14:17 by silndoj          ###   ########.fr       */
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
		if (mini.argc > 0)
		{
			execute(&mini);
			free_stuff(&mini);
		}
		unlink("here_doc.txt");
	}
}
