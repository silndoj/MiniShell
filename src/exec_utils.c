/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:57:53 by silndoj           #+#    #+#             */
/*   Updated: 2024/10/18 20:54:06 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	else_command(t_mini *mini)
{
	char	*path;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		path = find_path(mini->envp, *mini->commands[0]);
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
