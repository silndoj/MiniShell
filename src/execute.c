/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:58:31 by silndoj           #+#    #+#             */
/*   Updated: 2024/09/14 18:58:32 by silndoj          ###   ########.fr       */
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
	exit(127);
}

int	input_stuff(t_mini *mini, int *i)
{
	int		fdin;

	if (ft_strncmp(mini->arguments[*i], "<<", 3) == 0)
	{
		mini->fdin = open("here_doc.txt", O_CREAT | O_WRONLY | O_TRUNC, 06444);
		mini->fdin = create_here_doc(mini->arguments, *i, fdin);
		dup2(fdin, STDIN_FILENO);
		close(fdin);
		*i += 2;
	}
	else if (ft_strncmp(mini->arguments[*i], "<", 2) == 0)
	{
		fdin = open("here_doc.txt", O_CREAT | O_WRONLY | O_TRUNC, 06444);
		dup2(fdin, STDIN_FILENO);
		close(fdin);
		*i += 2;
	}
	return (fdin);
}

int	output_stuff(t_mini *mini, int i)
{
	int	fdout;

	if (ft_strncmp(mini->arguments[i + 1], ">", 2) == 0)
	{
		fdout = openfile(mini->arguments[i + 2], 1, 0);
		dup2(fdout, STDOUT_FILENO);
		return (fdout);
	}
	if (ft_strncmp(mini->arguments[i + 2], ">", 2) == 0)
	{
		fdout = openfile(mini->arguments[i + 3], 1, 0);
		dup2(fdout, STDOUT_FILENO);
		return (fdout);
	}
	if (ft_strncmp(mini->arguments[i + 2], ">>", 3) == 0)
	{
		fdout = openfile(mini->arguments[i + 3], 1, 1);
		dup2(fdout, STDOUT_FILENO);
		return (fdout);
	}
	return (1);
}

void	execute_pipes(t_mini *mini, int i)
{
	int		fdout;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		while (mini->arguments[i] != 0)
		{
			fdout = 1;
			input_stuff(mini, &i);
			fdout = output_stuff(mini, i);
			pipe_check(mini, fdout, &i);
			if (fdout != 1)
				i += 2;
		}
		exit(0);
	}
	waitpid(pid, &mini->exitcode, 0);
}

void	execute(t_mini *mini)
{
	int	i;

	i = 0;
	if (check_for_pipes(mini->line) == 0)
		execute_pipes(mini, 0);
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
	else if (ft_strncmp(mini->arguments[0], "ls", 3) == 0)
		ls(mini);
	else if (ft_strncmp(mini->arguments[0], "clear", 6) == 0)
		printf("\e[1;1H\e[2J");
}
