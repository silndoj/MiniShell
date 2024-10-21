/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:59:36 by silndoj           #+#    #+#             */
/*   Updated: 2024/10/21 03:31:58 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
