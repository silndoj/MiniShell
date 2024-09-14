/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:58:19 by silndoj           #+#    #+#             */
/*   Updated: 2024/09/14 18:58:21 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_check(t_mini *mini, int fdout, int	*i)
{
	if (ft_strncmp(mini->arguments[*i], "|", 1) == 0
		&& *i < mini->argc - 2)
	{
		redirect(mini->arguments[*i + 1], fdout, mini);
		*i += 2;
	}
	else if (ft_strncmp(mini->arguments[*i], "|", 1) == 0)
	{
		exec(mini->arguments[*i + 1], mini);
		*i += 2;
	}
	else if (ft_strncmp(mini->arguments[*i + 1], "|", 1) == 0
		&& *i < mini->argc - 2)
	{
		redirect(mini->arguments[*i], fdout, mini);
		*i += 1;
	}
	else
	{
		exec(mini->arguments[*i], mini);
		*i += 1;
		printf("%s\n", mini->arguments[*i]);
	}
}
