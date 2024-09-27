#include "minishell.h"

char	*pipe_cmd(char *line, int *i)
{
	int		j;
	char	*cmd;
	char	*sign;

	j = 0;
	sign = sign_check(line, i);
	if (ft_strncmp(sign, "0", 1) != 0)
		return (sign);
	while (line[*i + j] != '|' && line[*i + j] != '<'
		&& line[*i + j] != '>' && line[*i + j] != 0)
		j ++;
	cmd = malloc(j + 1);
	j = 0;
	while (line[*i] != '|' && line[*i] != '<'
		&& line[*i] != '>' && line[*i] != 0)
	{
		cmd[j] = line[*i];
		*i += 1;
		j ++;
	}
	cmd[j] = 0;
	return (cmd);
}
