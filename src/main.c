/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:59:36 by silndoj           #+#    #+#             */
/*   Updated: 2024/10/17 19:49:27 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_arguments(char **arguments)
{
	int	i;

	i = 0;
	while (arguments[i] != 0)
	{
		printf("%s\n", arguments[i]);
		fflush(stdout);
		i ++;
	}
}

void	init(t_mini *ministruct, char **envp)
{
	int	i;

	i = 0;
	read_perma_history();
	ministruct->nr_var = 0;
	ministruct->argc = 0;
	while (envp[i] != 0)
		i ++;
	ministruct->envp = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (envp[i] != 0)
	{
		if (ft_strncmp(envp[i], "SHLVL", 5) != 0)
			ministruct->envp[i] = ft_strdup(envp[i]);
		else
			ministruct->envp[i] = increment(envp[i]);
		i ++;
	}
	ministruct->envp[i] = 0;
	realloc_smaller_2d(ministruct, "OLDPWD");
}

int	main(int argc, char *argv[], char **env)
{
	t_mini	mini;
	char	mode;

	add_signalhandler(&mini);
	if (argc != 0)
		argv[1] = 0;
	init(&mini, env);
	loop_mini(mini);
	return (0);
}
