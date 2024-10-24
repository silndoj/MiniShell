/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 03:18:46 by silndoj           #+#    #+#             */
/*   Updated: 2024/10/23 20:34:47 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	redirect(char **command, t_io pipes[2], int ic, pid_t *pid)
{
	*pid = fork();
	if (*pid == CHILD)
		if (redirect_in(command) && connect(pipes, ic) && redirect_out(command))
			return (true);
	return (false);
}

void	builtin(t_mini *mini)
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
		exit_error("exit");
	else if (ft_strncmp(*mini->commands[0], "export", 7) == 0)
		ft_export(mini);
	else if (ft_strncmp(*mini->commands[0], "unset", 6) == 0)
		unset(mini);
	else
		else_command(mini, &mini->built);
}

char	*parse_cmd_single(char *line)
{
	int		i;
	char	*cmd;

	i = 1;
	while (isalpha(line[i]))
		i++;
	cmd = malloc(sizeof(char) * i);
	ft_strlcpy(cmd, line, i + 1);
	return (cmd);
}

void	execute(t_mini *mini, int ic)
{
	static t_io	pipes[2];
	bool		is_child;
	pid_t		pid;

	if (g_pipe_count && pipe(pipes[CURRENT]) == ERROR)
		exit_error("pipe");
	is_child = redirect(mini->commands[ic], pipes, ic, &pid);
	if (is_child)
	{
//		else_command(mini, &mini->built);
//		builtin(mini);
		execvp(mini->commands[ic][0], mini->commands[ic]);
//		free(mini->built);
		exit_error("execve");
	}
	close_(pipes, ic);
	alternate((int **)pipes);
}
