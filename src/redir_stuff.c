#include "minishell.h"
#include <sys/stat.h>
#include <unistd.h>

int	input_stuff(t_mini *mini, int *i)
{
	int		fdin;

	fdin = 0;
//	if (ft_strncmp(mini->arguments[*i], "<<", 3) == 0)
//	{
//		mini->fdin = open("here_doc.txt", O_CREAT | O_WRONLY | O_TRUNC, 06444);
//		mini->fdin = create_here_doc(mini->arguments, *i, fdin);
//		dup2(fdin, STDIN_FILENO);
//		close(fdin);
//	}
	if (ft_strncmp(mini->arguments[*i + 1], "<", 2) == 0)
	{
		fdin = open(mini->arguments[*i + 2], O_RDONLY, S_IRWXU);
		dup2(fdin, STDIN_FILENO);
		close(fdin);
		if (mini->arguments[*i + 3])
			*i += 3;
	}
	return (fdin);
}

int	output_stuff(t_mini *mini, int *i)
{
	int	fdout;

	fdout = 0;
	if (ft_strncmp(mini->arguments[*i + 1], ">", 2) == 0)
	{
		fdout = openfile(mini->arguments[*i + 2], 1, 0);
		dup2(fdout, STDOUT_FILENO);
		close(fdout);
		if (mini->arguments[*i + 3])
			*i += 3;
		return (fdout);
	}
//	if (ft_strncmp(mini->arguments[i + 2], ">", 2) == 0)
//	{
//		fdout = openfile(mini->arguments[i + 3], 1, 0);
//		dup2(fdout, STDOUT_FILENO);
//		return (fdout);
//	}
	if (ft_strncmp(mini->arguments[*i + 1], ">>", 3) == 0)
	{
		fdout = openfile(mini->arguments[*i + 2], 1, 1);
		dup2(fdout, STDOUT_FILENO);
		return (fdout);
	}
	return (1);
}

char	*rd_in(char *line, int *i)
{
	if (line[*i] == '<')
	{
		*i += 1;
		return (ft_strdup("<<"));
	}
	return (ft_strdup("<"));
}

char	*rd_out(char *line, int *i)
{
	if (line[*i] == '>')
	{
		*i += 1;
		return (ft_strdup(">>"));
	}
	return (ft_strdup(">"));
}

char	*sign_check(char *line, int *i)
{
	if (line[*i] == '|')
	{
		*i += 1;
		return (ft_strdup("|"));
	}
	if (line[*i] == '<')
	{
		*i += 1;
		return (rd_in(line, i));
	}
	if (line[*i] == '>')
	{
		*i += 1;
		return (rd_out(line, i));
	}
	return (ft_strdup("0"));
}
