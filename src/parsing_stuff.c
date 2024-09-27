/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:00:37 by silndoj           #+#    #+#             */
/*   Updated: 2024/09/20 17:04:11 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
