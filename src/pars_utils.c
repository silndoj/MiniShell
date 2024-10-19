/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:00:22 by silndoj           #+#    #+#             */
/*   Updated: 2024/10/17 19:40:06 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_short2(int *counter, char **cmd, char c)
{
	cmd[0]++;
	counter[0]++;
	while (cmd[0][0] != c)
		cmd[0]++;
	cmd[0]++;
}

char	*ft_str_safe(char **cmd, char c, char a, char b)
{
	int		j;
	char	*string;

	j = 0;
	while (cmd[0][j] != c && cmd[0][j] != 0)
		j++;
	string = malloc ((j + 1) * sizeof(char));
	j = 0;
	while (*cmd[0] != c && *cmd[0] != b && *cmd[0] != a && *cmd[0] != 0)
	{
		string[j] = *cmd[0];
		j ++;
		cmd[0]++;
	}
	string[j] = 0;
	return (string);
}

void	ft_short(int *i, char **commands, char **cmd, char c)
{
	cmd[0]++;
	commands[*i] = ft_str_safe(cmd, c, 0, 0);
	*i += 1;
	cmd[0]++;
}
