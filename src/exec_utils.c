/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:57:53 by silndoj           #+#    #+#             */
/*   Updated: 2024/09/14 18:57:55 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ls(t_mini *mini)
{
	char	*path;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		path = find_path(mini->envp, mini->arguments[0]);
		execve(path, mini->arguments, mini->envp);
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
		j = check_envp(mini, mini->arguments[i]);
		string = ft_strjoin(mini->arguments[i], "=");
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

void	redirect(char *cmd, int fdout, t_mini *mini)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
	else
	{
		close(pipefd[0]);
		if (fdout == 1)
			dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		exec(cmd, mini);
	}
}
