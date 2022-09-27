/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 09:46:20 by blevrel           #+#    #+#             */
/*   Updated: 2022/09/27 14:44:41 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct s_cmd
{
	char	**cmd;
	char	*path;
	char	*type;
	char	*file;
	char 	**limiter;
}			t_cmd;

typedef struct s_data
{
	char	**envp;
	char	**export;
	char	**parsing;
	char	*tokenized_str;
	char	*arg;
	pid_t	*son;
	t_cmd	**cmd;
	int		**pipexfd;
}				t_data;

int		simple_cmd(t_data *data);

//INIT_STRUCT_COMMAND
int		check_open(char **cmd);
int		nb_cmd(char **argv, int i);
int		check_redirection_pipe(char *str);
int		check_nbpipe(char **argv);
int		check_index_pipe(char **argv, int index_pipe);
t_cmd	*init_simple_struct(t_data *data, int index_pipe);
t_cmd	**init_struct_cmd(t_data *data);
int		check_command(char *str);
char	**sort_env(char **env);
void	init_null_cmd(t_cmd *res);
void	init_data(t_data *data, char **env);

//REDIRECTION
int		check_redirection(t_data *data);
void	here_doc(t_cmd *cmd, char **env);
void	here_doc_pipe(t_cmd *cmd, int **pippexfd, char **env, int i);

//SIGNALS
void	catch_signal(int signal);
void	signal_handler(void);

//UTILS
int		ft_strchr_int(const char *s, int c);
void	free_double_tab(char **tab);
int		check_char(char c);
void	swap_str(char **s1, char **s2);
int		size_tab(char **tab);
char	**cpy_tab(char **dest, char **src);

//CHECK_PATH
void	*cmd_not_found(char *cmd);
char	*check_path(char *cmd, char **env);

//PARSING
int		check_closing_quotes(char *str);
void	fill_cmd_quotes(char *arg, int *i, char *cmd, int c);
char	**check_arg(char **cmd, char c);
void	fill_cmd_tab(char *arg, int *i, char *cmd, int *trigger);
void	fill_cmd_space(char *arg, int *i, int *trigger);
void	fill_cmd_redirection(char *arg, int *i, char *cmd, int *j);
char	last_non_spc_char(int i, char *str);
char	next_non_spc_char(int i, char *str);
char	last_diff_and_non_spc_char(int i, char *str);
void	parsing_arg(t_data *data);
void	cmd_tab_size_quotes(int *i, char *arg, int c);
void	fill_cmd_tab_with_quotes(int *i, char *arg, char *cmd, int c);
int		allocate_cmd_with_quotes(int *i, char *arg, int *trigger, int c);
int		alloc_multitab(char *arg, int *i, int *size);
void	allocate_cmd(char *arg, char **cmd, int tab_size);
int		get_cmd_tab_size(char *arg);
int		parsing_with_quotes(char *arg, int *i, int *not_first_arg,
			int c);
int		parsing_with_redirection(char *arg, int *i, int *not_first_arg,
			int size);
int		parsing_with_space(char *arg, int *i, int *not_first_arg,
			int *trigger);
int		parsing_with_quotes_first_arg(char *arg, int *i, int size,
			int *not_first_arg);
int		reset_statics(int *i, int *trigger, int size);

//TOKENIZING
void	tokenize(t_data *data);
int		get_tokenizing_size(char *cmd, char **envp);
char	*isolate_env_var(char *cmd);
int		get_env_variable_size(char *to_find, char **envp);
void	get_env_variable(t_data *data, int *i, int *j, int cmd_index);
void	fill_new_cmd(t_data *data, int size, int cmd_index);
void	fill_tokenized_cmd_with_quotes(t_data *data, int *i, int *j,
			int cmd_index);
void	fill_single_quotes(t_data *data, int *i, int *j, int cmd_index);
void	fill_double_quotes(t_data *data, int *i, int *j, int cmd_index);
void	fill_env_variable(t_data *data, int *j, char *env_var_line);

//QUOTES
int		get_quote_modif_size(char *cmd, char **envp, int *i);
int		get_single_quote_size(char *cmd, int *i);
int		get_double_quote_size(char *cmd, int *i, char **emvp);

//BUILTIN
int		check_builtin(t_cmd *cmd, t_data *data);
void	echo(t_cmd *data);
void	pwd(void);
void	env(char **env);
void	directory(t_cmd *cmd,t_data *data); 
void	ft_export(t_cmd *cmd, t_data *data);
void	unset(t_cmd *cmd, t_data *data);

//PIPE
int		check_pipe(t_data *data);
int		ft_pipe(t_data *data);
int		check_nbpipe(char **argv);
void	check_dup_pipe_first(t_cmd *cmd, int **pipexfd, int i);
void	check_dup_pipe_n(t_cmd *cmd, int **pipexfd, int i);
void	check_dup_pipe_last(t_cmd *cmd, int **pipexfd, int i);

//EXPORT
char	**new_env_export(char **cmd, char **env);
char	**new_export(t_cmd *cmd, t_data *data);
char	**sort_env(char **env);
void	print_export(char **print);
int		search_env(char *str, char **env);
char	**fill_new_export(char **new_export, t_cmd *cmd, t_data *data, int i);
void	replace_value(char *str, int line, t_data *data);
char	**replace_value_export(char *str, int line, char **export);
int		search_new_env(char **cmd, char **env);
int		check_value(char *str);

//UNSET
int	check_unset(char *str, char **env);
char **new_tab(int i, char **src);

//FREE
void	free_parsing(t_data *data);
void	free_simple_cmd(t_cmd *cmd);
void	free_multiple_cmd(t_data *data);
void	free_data(t_data *data);

#endif
