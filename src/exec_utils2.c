/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:58:07 by silndoj           #+#    #+#             */
/*   Updated: 2024/09/14 18:58:09 by silndoj          ###   ########.fr       */
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

int	ft_search_out(char **args, int i)
{
	int	j;

	j = i;
	while (args[j] != 0 && j < i + 2)
		j ++;
	if (ft_strncmp(args[j], ">", 2) == 0)
		return (0);
	return (1);
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

void	exit_programm(t_mini *mini)
{
	free_stuff(mini);
	free_function(mini);
	exit(0);
}

int	openfile(char *filename, int mode, int is_here_doc)
{
	if (mode == 0)
	{
		if (access(filename, F_OK))
			return (STDIN_FILENO);
		return (open(filename, O_RDONLY));
	}
	else if (is_here_doc == 0)
		return (open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0666));
	else
		return (open(filename, O_CREAT | O_WRONLY | O_APPEND, 0666));
}
