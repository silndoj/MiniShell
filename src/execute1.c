/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:04:20 by silndoj           #+#    #+#             */
/*   Updated: 2024/10/20 17:39:56 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

static bool	redirect(char **command, t_io pipes[2], int ic, pid_t *pid)
{
	*pid = fork();
	if (*pid == CHILD)
		if (redirect_in(command) && connect(pipes, ic) && redirect_out(command))
			return (true);
	return (false);
}

void	execute1(t_mini *mini)
{
	if (ft_strncmp(*mini->commands[0], "env", 4) == 0)
		show_env(mini);
	else if (ft_strchr(*mini->commands[0], '=') != 0)
		save_var(mini, 0);
	else if (ft_strncmp(*mini->commands[0], "cd", 3) == 0)
		change_directory(*mini->commands[1], mini);
	else if (ft_strncmp(*mini->commands[0], "pwd", 4) == 0)
		show_path(mini);
	else if (ft_strncmp(*mini->commands[0], "echo", 5) == 0)
		echo(mini, 0);
	else if (ft_strncmp(*mini->commands[0], "exit", 5) == 0)
		exit_programm(mini);
	else if (ft_strncmp(*mini->commands[0], "export", 7) == 0)
		ft_export(mini);
	else if (ft_strncmp(*mini->commands[0], "unset", 6) == 0)
		unset(mini);
	else
		else_command(mini);
}

void	execute(char **command, int ic)
{
	static t_io	pipes[2];
	bool		is_child;
	int			i;
	pid_t		pid;

	i = 0;
	if (g_pipe_count && pipe(pipes[CURRENT]) == ERROR)
		exit_error("pipe");
	is_child = redirect(command, pipes, ic, &pid);
	if (is_child)
	{
		execvp(command[0], command);
		exit_error("execvp");
	}
	waitpid(pid, NULL, 0);
	close_(pipes, ic);
	alternate((int **)pipes);
}
