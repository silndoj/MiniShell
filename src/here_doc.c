/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 03:15:06 by silndoj           #+#    #+#             */
/*   Updated: 2024/10/21 03:15:12 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_check(char **arg, int i, int fd, t_char *cset)
{
	int	j;

	j = 0;
	while (1)
	{
		read(0, cset->buffer, 1);
		cset->cm = ft_strjoin2(cset->cm, cset->buffer);
		j = ft_strlen(cset->cm);
		if (ft_strncmp(cset->buffer, "\n", 1) == 0)
		{
			if (ft_strncmp(cset->cm, arg[i + 1], j - 1) == 0)
			{
				free(cset->cm);
				cset->cm = 0;
				break ;
			}
			else
			{
				write(fd, cset->cm, ft_strlen(cset->cm));
				free(cset->cm);
				cset->cm = 0;
			}
		}
	}
}

int	create_here_doc(char **arguments, int i, int fdin)
{
	t_char	cm_set;
	char	*command_line;

	cm_set.buffer[1] = 0;
	command_check(arguments, i, fdin, &cm_set);
	close(fdin);
	fdin = open("here_doc.txt", O_WRONLY, 0644);
	return (fdin);
}
