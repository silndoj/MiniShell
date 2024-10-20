/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuhn <kkuhn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 17:27:53 by kkuhn             #+#    #+#             */
/*   Updated: 2024/10/20 17:16:33 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../tools/libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/wait.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <termios.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>

# define ERROR -1
# define INTERACTIVE 0
# define COMMANDLINE 1
# define CHILD 0
# define CURRENT 0
# define PREVIOUS 1
# define READ 0
# define WRITE 1
# define TRUNCATE 1
# define APPEND 2

typedef int	t_io[2];
extern int	g_pipe_count;

typedef struct var_t
{
	char	buffer[2];
	char	*cm;
}	t_char;

typedef struct variable_t
{
	char	*name;
	char	*value;
}	t_var;

typedef struct mini_t
{
	int		exitcode;
	int		exitstatus;
	char	*line;
	char	**envp;
	t_var	*variables;
	size_t	nr_var;
	char	***commands;
	int		finished;
	int		fdin;
	int		fdout;
	int		argc;
}	t_mini;

bool	redirect_in(char **arguments);
bool	redirect_out(char **arguments);
void	execute(char **command, int ic);
char	***parse(char *line);
void	free_strings(char **strings);
void	exit_error(const char *message);
bool	connect(t_io pipes[2], int ic);
void	close_(t_io pipes[2], int ic);
void	alternate(int **pipes);
void	erase_from(char **strings, size_t count);
void	*xmalloc(size_t size);

//EXEC_FILES
void	exec(char *cmd, t_mini *mini);
void	execute1(t_mini *mini);
void	unset(t_mini *mini);
void	exit_programm(t_mini *mini);
void	echo(t_mini *mini, int i);
void	show_env(t_mini *mini);
void	change_directory(char *path, t_mini *mini);
void	show_path(t_mini *mini);
void	else_command(t_mini *mini);
void	new_line(void);
void	ft_export(t_mini *mini);

//UTILS
int		check_envp(t_mini *mini, char *argument);
char	*find_path(char *envp[], char *cmd);
char	*ft_remove_space(char *cmd);
char	*remove_end_spaces(char *string);
char	*increment(char *string);
void	command_check(char **arg, int i, int fd, t_char *cset);
int		create_here_doc(char **arguments, int i, int fdin);
char	*ft_str_safe(char **cmd, char c, char a, char b);
char	*ft_strjoin2(char *s1, char *s2);
void	ft_short(int *i, char **commands, char **cmd, char c);
int		count_parts(char *cmd);
char	**cmd_in_folder(char *cmd);
char	*sign_check(char *line, int *i);

//INIT
void	print_arguments(char **arguments);
void	init(t_mini *ministruct, char **envp);
void	loop_mini(t_mini mini);

//ALLOCATIONS
void	free_2dchar(char **array);
void	realloc_smaller_2d(t_mini *mini, char *string);
char	**realloc_2dchar(char **src, char *string, int i);
void	free_function(t_mini *ministruct);
void	free_stuff(t_mini *mini);

//SIGNALS
void	handle_sigint(int sig);
void	handle_sigterm(int sig);
void	add_signalhandler(t_mini *mini);

//HISTORY
void	read_perma_history(void);
void	perma_history(char *cmdline);

//PARSING
char	**allocate_command(char *cmd, t_mini *mini, int i);
int		search_var(t_mini *mini, char *string);
void	save_var(t_mini *mini, int i);
char	*var_value(char *string, int i);
void	arg_read(char *cmd, char **commands, int i, int size);

#endif
