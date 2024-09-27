/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:01:12 by silndoj           #+#    #+#             */
/*   Updated: 2024/09/20 16:24:39 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_remove_space(char *cmd)
{
	int		j;
	int		i;

	i = 0;
	j = 0;
	while (cmd[i + j] != 0)
	{
		if (cmd[i + j] == ' ')
			j ++;
		if (cmd[i + j] == '\"')
			cmd[i] = '\"';
		else
			cmd[i] = cmd[i + j];
		i ++;
	}
	cmd[i + j] = 0;
	return (cmd);
}

char	*increment(char *string)
{
	char	*number;
	char	*returnstring;
	int		nr;

	number = ft_strchr(string, '=') + 1;
	nr = ft_atoi(number) + 1;
	number = ft_itoa(nr);
	returnstring = ft_strjoin("SHLVL=", number);
	free(number);
	return (returnstring);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == 0)
		return (ft_strdup(s2));
	result = malloc (ft_strlen(s1) + ft_strlen(s2) + 1);
	while (s1[i] != 0)
	{
		result[i] = s1[i];
		i ++;
	}
	while (s2[j] != 0)
	{
		result[i] = s2[j];
		i ++;
		j ++;
	}
	result[i] = 0;
	free(s1);
	return (result);
}

char	*find_path(char *envp[], char *cmd)
{
	int		i;
	char	*path;
	char	*part_path;
	char	**paths;

	i = 0;
	if (ft_strnstr(&cmd[0], ".sh", ft_strlen(&cmd[0])) != 0
		|| ft_strnstr(&cmd[0], "/", ft_strlen(&cmd[0])) != 0)
		return (ft_remove_space(&cmd[0]));
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i ++;
	paths = ft_split(&envp[i][5], ':');
	i = -1;
	while (paths[++ i] != 0)
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (free_2dchar(paths), path);
		free(path);
	}
	free_2dchar(paths);
	return (0);
}
