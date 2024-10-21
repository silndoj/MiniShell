/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:57:53 by silndoj           #+#    #+#             */
/*   Updated: 2024/10/21 03:34:09 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	else_command(t_mini *mini)
{
	char	*path;
	pid_t	pid;

	path = malloc(1024);
	pid = fork();
	if (pid == 0)
	{
		path = getcwd(path, 1024);
		execve(path, *mini->commands, mini->envp);
	}
	waitpid(pid, NULL, 0);
}

void	unset(t_mini *mini)
{
	int		j;
	char	*string;
	int		i;

	i = 0;
	if (mini->argc < 2)
		return ;
	while (++ i < mini->argc)
	{
		j = check_envp(mini, *mini->commands[i]);
		string = ft_strjoin(*mini->commands[i], "=");
		if (j == 0)
		{
			free(string);
			return ;
		}
		else
			realloc_smaller_2d(mini, string);
		free(string);
	}
}
