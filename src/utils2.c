/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:01:36 by silndoj           #+#    #+#             */
/*   Updated: 2024/09/20 16:27:32 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cmd_in_folder(char *cmd)
{
	char	**command;

	command = malloc (2 * sizeof(char *));
	command[0] = ft_strdup(cmd);
	command[1] = 0;
	return (command);
}

char	*remove_end_spaces(char *string)
{
	int		i;
	int		store_size;
	int		count_spaces;
	char	*result;

	i = ft_strlen(string);
	store_size = i;
	count_spaces = 0;
	while (string[i - 1] == ' ' && i > 0)
	{
		count_spaces ++;
		i --;
	}
	result = malloc(store_size + 1 - count_spaces);
	i = 0;
	while (i < store_size - count_spaces)
	{
		result[i] = string[i];
		i ++;
	}
	result[i] = 0;
	free(string);
	return (result);
}
