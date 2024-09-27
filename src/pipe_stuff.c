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

void	pipe_check(t_mini *mini, int fdout, int	*i)
{
	if (ft_strncmp(mini->arguments[*i], "|", 1) == 0
		&& *i < mini->argc - 2)
	{
		redirect(mini->arguments[*i + 1], fdout, mini);
		*i += 2;
	}
	else if (ft_strncmp(mini->arguments[*i], "|", 1) == 0)
	{
		exec(mini->arguments[*i + 1], mini);
		*i += 2;
	}
	else if (ft_strncmp(mini->arguments[*i + 1], "|", 1) == 0
		&& *i < mini->argc - 2)
	{
		redirect(mini->arguments[*i], fdout, mini);
		*i += 1;
	}
	else
	{
		exec(mini->arguments[*i], mini);
		*i += 1;
		printf("%s\n", mini->arguments[*i]);
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

void	execute_wpipes(t_mini *mini, int i)
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
