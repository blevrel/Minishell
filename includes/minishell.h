/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 09:46:20 by blevrel           #+#    #+#             */
/*   Updated: 2022/09/05 13:42:34 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct s_cmd
{
	char **cmd;
	char *path;
	char *type;
	char *file;
}	t_cmd;

typedef struct	s_data
{
	char **envp;
	char **cmd;
	char *arg;
	pid_t *son;
	t_cmd **pipex;
}	t_data;

int		simple_cmd(t_data *data);

//REDIRECTION
void	entry_red(t_data *data);
void	exit_red(t_data *data);
int		check_redirection(t_data *data);
void	here_doc(t_data *data);
int		check_double_red(t_data *data);
void	append(t_data *data);

//SIGNALS
void	catch_signal(int signal);
void	signal_handler(void);

//UTILS
int		ft_strchr_int(const char *s, int c);
void	free_double_tab(char **tab);
int		check_char(char c);

//CHECK_PATH
void	*cmd_not_found(char *cmd);
char	*check_path(char *cmd, char **env);

//PARSING
char	**check_arg(char **cmd, char c);
int		check_quotes(t_data *data, int i);
void	modify_quotes(t_data *data, int i);
void	modify_single_quotes(char *cmd, int len);
void	modify_double_quotes(char *cmd, int len);
char	check_last_non_spc_char(int i, char *str);
char	check_next_non_spc_char(int i, char *str);
void	parsing_arg(t_data *data);
int		cmd_tab_size_quotes(int *i, char *arg, int c);
void	fill_cmd_tab_with_quotes(int *i, char *arg, char *cmd, int c);
int		allocate_cmd_with_quotes(int *i, char *arg, int *trigger, int c);

//BUILDIN
void	echo(t_data *data);

//PIPE
int		check_pipe(t_data *data);
int		ft_pipe(t_data *data);
int		check_nbpipe(char **argv);
t_cmd	**init_struct_pipe(t_data *data);
void	check_dup_pipe_first(t_cmd *cmd, int **pipexfd, int i);
void	check_dup_pipe_n(t_cmd *cmd, int **pipexfd, int i);
void	check_dup_pipe_last(t_cmd *cmd, int **pipexfd, int i);
/*void	first_pipe(int	**pipexfd, t_data *cmd);
void	mid_pipe(int	**pipexfd, t_data *cmd, int i);
void	last_pipe(int	**pipexfd, t_data *cmd, int i);
int		first_simple_call(int *pipexfd, t_data *data);
int		mid_simple_call(int *pipe, int *pipenext, t_data *data, int i);
int		last_simple_call(int *pipe, int i, t_data *data);
int		check_builtin_first(int	*pipexfd, t_data *data, int i);
int		check_builtin_mid(int	*pipe, int *pipenext, t_data *data, int i);
int		check_builtin_last(int	*pipexfd, t_data *data, int i);
char	**copy_cmd(char **cmd, t_data *data, char *red, int indexpipe);
*/
