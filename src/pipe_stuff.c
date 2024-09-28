#include "minishell.h"

void	parse_pipe_cmd(char **cmd, int *i, char **p)
{
	char	*string;

	if ((p[0][0] == '<' || p[0][0] == '>') && p[0][0] == p[0][1])
	{
		cmd[*i] = malloc(3);
		cmd[*i][0] = p[0][0];
		cmd[*i][1] = p[0][0];
		cmd[*i][2] = 0;
		p[0] += 2;
	}
	else
	{
		cmd[*i] = malloc(2);
		cmd[*i][0] = p[0][0];
		cmd[*i][1] = 0;
	}
	*i += 1;
	p[0] += 1;
	while (p[0][0] == ' ')
		p[0]++;
	string = ft_str_safe(&p[0], '|', '<', '>');
	cmd[*i] = remove_end_spaces(string);
	*i += 1;
}

void	pipe_check(t_mini *mini, int *i)
{
//	if (ft_strncmp(mini->arguments[*i], "|", 1) == 0
//		&& *i < mini->argc - 2)
//	{
//		*i += 2;
//	}
	if (ft_strncmp(mini->arguments[*i], "|", 1) == 0)
	{

		redirect(mini->arguments[*i + 1], mini->fdout, mini);
		exec(mini->arguments[*i + 1], mini);
		*i += 2;
	}
	else if (ft_strncmp(mini->arguments[*i + 1], "|", 1) == 0
		&& *i < mini->argc - 2)
	{
		redirect(mini->arguments[*i], mini->fdout, mini);
		*i += 1;
	}
	else
	{
		exec(mini->arguments[*i], mini);
		*i += 1;
	}
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
			mini->fdin = input_stuff(mini, &i);
			mini->fdout = output_stuff(mini, i);
			pipe_check(mini, &i);
			if (fdout != 1)
				i += 2;
		}
		exit(0);
	}
	waitpid(pid, &mini->exitcode, 0);
//	parent_time(mini->arguments[i - 1]);
}

int	check_for_pipes(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == '<' || str[i] == '|' || str[i] == '>')
			return (0);
		i++;
	}
	return (1);
}

//void	parent_time(char *arg)
//{
//	int		fileout;
//
//	fileout = open(, O_WRONLY | O_CREAT | O_TRUNC, 0777);
//	if (fileout == -1)
//		error();
//	dup2(fd[0], STDIN_FILENO);
//	dup2(fileout, STDOUT_FILENO);
//	close(fd[1]);
//	execute(argv[3], envp);
//}
