/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:58:31 by silndoj           #+#    #+#             */
/*   Updated: 2024/09/28 00:21:36 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(char *cmd, t_mini *mini)
{
	char	**args;
	char	*path;

	args = allocate_command(cmd, mini, 0);
	path = find_path(mini->envp, args[0]);
	if (path == 0)
	{
		free_2dchar(args);
		exit(127);
	}
	execve(path, args ,mini->envp);
	exit(127);
}

void	execute(t_mini *mini)
{
	int	i;

	i = 0;
	if (check_for_pipes(mini->line) == 0)
		execute_pipes(mini, 0);
//	else
//		execute_wpipes(mini, 0);
	else if (ft_strncmp(mini->arguments[0], "env", 4) == 0)
		show_env(mini);
	else if (ft_strchr(mini->arguments[0], '=') != 0)
		save_var(mini, 0);
	else if (ft_strncmp(mini->arguments[0], "cd", 3) == 0)
		change_directory(mini->arguments[1], mini);
	else if (ft_strncmp(mini->arguments[0], "pwd", 4) == 0)
		show_path(mini);
	else if (ft_strncmp(mini->arguments[0], "echo", 5) == 0)
		echo(mini, 0);
	else if (ft_strncmp(mini->arguments[0], "exit", 5) == 0)
		exit_programm(mini);
	else if (ft_strncmp(mini->arguments[0], "export", 7) == 0)
		ft_export(mini);
	else if (ft_strncmp(mini->arguments[0], "unset", 6) == 0)
		unset(mini);
	else
		else_command(mini);
}
