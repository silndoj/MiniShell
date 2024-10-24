/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:59:36 by silndoj           #+#    #+#             */
/*   Updated: 2024/10/24 19:04:10 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

int	main(int argc, char *argv[], char **env)
{
	t_mini	mini;

	gc_init_garbage_collector();
	add_signalhandler(&mini);
	if (argc != 0)
		argv[1] = 0;
	init(&mini, env);
	loop_mini(mini);
	return (0);
}
