/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 09:46:20 by blevrel           #+#    #+#             */
/*   Updated: 2022/10/19 03:39:07 by blevrel          ###   ########.fr       */
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
# define IN_PARENT 0
# define IN_HERE_DOC 1
# define IN_COMMAND 2

int	g_signal_trigger;

typedef struct s_cmd
{
	char	**cmd;
	char	*path;
	char	*type;
	char	*file;
	char	**limiter;
}			t_cmd;

typedef struct s_data
{
	char	**envp;
	char	**export;
	char	**parsing;
	char	*arg;
	pid_t	*son;
	t_cmd	**cmd;
	int		**pipexfd;
}				t_data;

int		simple_cmd(t_data *data);

//INIT_STRUCT_COMMAND
int		check_open(char **cmd);
int		nb_cmd(char *full_arg);
int		check_redirection_pipe(char *str);
int		check_nbpipe(char *full_arg);
int		check_index_pipe(char **argv, int index_pipe);
t_cmd	*init_simple_struct(t_data *data, int index_pipe, t_cmd **cmd_pipe);
t_cmd	**init_struct_cmd(t_data *data);
t_cmd	*fill_simple_cmd(t_data *data, t_cmd *cmd, int i, int j);
void	init_file(t_cmd *res, t_data *data, int i);
int		check_command(char *str);
char	**sort_env(char **env);
void	init_null_cmd(t_cmd *res);
void	init_data(t_data *data, char **env);

//REDIRECTION
int		check_redirection(char *str);
int		check_only_redirection(char *str, char *full_arg);
void	here_doc(t_cmd *cmd, char **env);
void	here_doc_pipe(t_cmd *cmd, int **pippexfd, char **env, int i);
char	*tokenize_here_doc_limiter(char *str);
char	*fill_limiter(char *str, char *res);

//SIGNALS
void	catch_signal(int signal);
void	signal_handler(void);

//UTILS
int		verif_malloc_arr(char **arr);
int		verif_malloc_str(char **arr, int line);
int		verif_malloc_int_arr(int **arr);
int		verif_malloc_int(int **arr, int line);
int		verif_malloc_t_cmd(t_cmd *arr, int line, t_cmd **cmd_pipe);
int		ft_strchr_int(const char *s, int c);
int		ft_strnchr_int(const char *s, int c, int size);
void	free_double_tab(char **tab);
int		check_char(char *str);
void	swap_str(char **s1, char **s2);
int		size_tab(char **tab);
char	**cpy_tab(char **dest, char **src);
char	next_non_spc_char(int i, char *str);

//CHECK_PATH
void	*cmd_not_found(char *cmd);
char	*check_path(char *cmd, char **env);

//CHECK_SYNTAX_ERROR
char	*check_syntax_error(char *str);
char	*check_here_doc(char *str, int *i);

//PARSING / TOKENIZING
char	**alloc_final_tab(t_data *data);
char	**fill_final_tab(char **final_tab, t_data *data, int *i, int *j);
int		check_size_first_arg(char *arg, int i);
int		alloc_with_quotes(char **final_tab, char *arg, int *i, int *j);
int		alloc_until_pipe(char **final_tab, char *arg, int i, int j);
int		go_to_first_arg(char *arg, int *i);
int		count_arg(char *arg, int *i);
int		nb_arg(char *arg);
int		count_size_first_arg(char *arg);
int		count_size_arg(char *arg, int value);
void	fill_arg(char *final_tab, char *arg, int *i, int value);
int		fill_until_pipe(char **final_tab, char *arg, int *i, int *j);
char	*alloc_first_arg(char *arg, int *i);
char	*fill_first_arg(char *arg, char *res, int *i, int *j);
int		size_tokenize(char *src, char **env);
char	**tokenizing(t_data *data);
int		check_quote(char *arg, int *i);
int		check_closing_quotes(char *arg);
int		size_in_quote(char *str, int *i, int quote, char **env);
int		size_tokenize(char *src, char **env);
void	fill_tokenized_with_quote(char **envp, char *res, char *src, int quote);
void	tokenize_arg(char *res, char *src, t_data *data);
int		size_env(char *str);
char	*isolate_env_var(char *cmd);
int		get_env_variable_size(char *cmd, char **envp);
void	fill_env(char *res, char *str, char **env, int *j);
void	move_indextoenv(char *str, int *i);
int		move_index_after_quote(char *str, int i, int quote);

//BUILTIN
int		check_builtin(t_cmd *cmd, t_data *data);
int		check_echo_option(char *full_arg, char **cmd);
int		check_multiple_options(char *res);
int		check_option_format(char *full_arg, char *option);
int		is_valid_option(char **cmd, int cmd_i);
void	echo(char **cmd, t_data *data, int i, int arg_i);
void	pick_correct_echo(t_cmd *cmd, t_data *data);
void	echo_n(char **cmd, char *full_arg, int arg_i, int cmd_i);
int		move_cmd_arr_index(char **cmd, char *options);
char	*join_echo_options(char **cmd, char *full_arg);
char	*replace_env_in_full_arg(char *full_arg, char **env);
int		move_arg_i_in_quote(char *full_arg, int arg_i);
int		check_if_space_is_needed(char *cmd, char *first_occ);
int		move_arg_i(char *full_arg, int arg_i);
void	add_space_if_needed(char *cmd, char *first_occ);
void	pwd(void);
void	env(char **env);
void	ft_exit(t_data *data);
void	check_exit_arg(char **args, int *exit_arg);
void	directory(t_cmd *cmd, t_data *data);
void	ft_export(t_cmd *cmd, t_data *data);
void	unset(t_cmd *cmd, t_data *data);

//PIPE
int		check_pipe(t_data *data);
int		ft_pipe(t_data *data);
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
int		check_unset(char *str, char **env);
char	**new_tab(int i, char **src);

//FREE
void	free_parsing(t_data *data);
void	free_simple_cmd(t_cmd *cmd);
void	free_multiple_cmd(t_data *data);
void	free_data(t_data *data);

#endif
