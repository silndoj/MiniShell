/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:37:16 by silndoj           #+#    #+#             */
/*   Updated: 2024/10/17 19:44:02 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	connect(t_io pipes[2], int ic)
{
	if (g_pipe_count)
	{
		if ((ic == g_pipe_count) || ic != 0)
			dup2(pipes[PREVIOUS][READ], STDIN_FILENO);
		if (ic == 0 || !(ic == g_pipe_count))
			dup2(pipes[CURRENT][WRITE], STDOUT_FILENO);
	}
	return (true);
}

void	close_(t_io pipes[2], int ic)
{
	if (g_pipe_count)
	{
		if ((ic == g_pipe_count) || ic != 0)
			close(pipes[PREVIOUS][READ]);
		if (ic == 0 || !(ic == g_pipe_count))
			close(pipes[CURRENT][WRITE]);
	}
}

void	alternate(int **pipes)
{
	int	*pipe_current;

	pipe_current = pipes[CURRENT];
	pipes[CURRENT] = pipes[PREVIOUS];
	pipes[PREVIOUS] = pipe_current;
}
