/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:59:36 by silndoj           #+#    #+#             */
/*   Updated: 2024/09/14 19:15:01 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char **env)
{
	t_mini	mini;

	add_signalhandler(&mini);
	if (argc != 0)
		argv[1] = 0;
	init(&mini, env);
	loop_mini(mini);
	free_function(&mini);
	return (0);
}
