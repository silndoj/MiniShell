/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:00:37 by silndoj           #+#    #+#             */
/*   Updated: 2024/09/14 19:00:39 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	arg_read(char *cmd, char **commands, int i, int size)
{
	while (i < size)
	{
		if (*cmd != ' ' && *cmd != '\'' && *cmd != '"')
		{
			commands[i] = ft_str_safe(&cmd, ' ', 0, 0);
			i ++;
		}
		else if (*cmd == '\'')
			ft_short(&i, commands, &cmd, '\'');
		else if (*cmd == '"')
			ft_short(&i, commands, &cmd, '"');
		else if (*cmd == ' ')
			cmd ++;
	}
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
