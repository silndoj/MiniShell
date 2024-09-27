#include "minishell.h"

char	**alloc_pipes(t_mini *mini, char **cmd)
{
	int		i;
	int		j;
	char	*string;

	i = 0;
	j = 0;
	while (mini->line[i] != 0)
	{
		while (mini->line[i] == ' ')
			i ++;
		string = pipe_cmd(mini->line, &i);
		cmd[j] = remove_end_spaces(string);
		j ++;
	}
	cmd[j] = 0;
	return (cmd);
}

char	**allocate_command(char *cmd, t_mini *mini, int i)
{
	char	**commands;
	int		size;

	if (ft_memcmp(cmd, "./", 2) == 0)
		return (cmd_in_folder(cmd));
	size = count_parts(cmd);
	if (mini->argc == 0)
		mini->argc = size;
	commands = malloc ((size + 1) * sizeof(char *));
	if (check_for_pipes(cmd) == 0)
		return (alloc_pipes(mini, commands));
	arg_read(cmd, commands, i, size);
	commands[size] = 0;
	return (commands);
}
