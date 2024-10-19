/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:59:01 by silndoj           #+#    #+#             */
/*   Updated: 2024/10/18 20:54:23 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	realloc_smaller_2d(t_mini *mini, char *string)
{
	char	**envp;
	int		i;
	int		j;

	i = 0;
	while (mini->envp[i] != 0)
		i ++;
	envp = malloc((i) * sizeof(char *));
	i = 0;
	j = 0;
	while (mini->envp[j] != 0)
	{
		if (ft_strncmp(mini->envp[j], string, ft_strlen(string)) != 0)
		{
			envp[i] = ft_strdup(mini->envp[j]);
			i ++;
		}
		j ++;
	}
	envp[i] = 0;
	free_2dchar(mini->envp);
	mini->envp = envp;
}

void	free_function(t_mini *mini)
{
	free_2dchar(mini->envp);
	while (mini->nr_var > 0)
	{
		free(mini->variables[mini->nr_var - 1].name);
		free(mini->variables[mini->nr_var - 1].value);
		mini->nr_var --;
	}
	if (mini->variables != 0)
		free(mini->variables);
}

void	free_stuff(t_mini *mini)
{
	if (mini->line)
		free(mini->line);
	free_2dchar(*mini->commands);
}

void	free_2dchar(char **array)
{
	int	i;

	i = 0;
	while (array[i] != 0)
		free(array[i++]);
	free(array);
}
