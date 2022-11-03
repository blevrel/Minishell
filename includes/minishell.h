/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 09:46:20 by blevrel           #+#    #+#             */
/*   Updated: 2022/11/03 16:26:08 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
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
	char	*infile;
	char	*outfile_append;
	char	*outfile;
	int		heredoc;
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
	int		return_value;
}				t_data;

int		simple_cmd(t_data *data);
void	return_value(int *son, t_data *data, int size);

//INIT_STRUCT_COMMAND
int		check_open(char **cmd);
int		nb_cmd(char *full_arg, int index_pipe);
int		check_redirection_pipe(char *str);
int		check_nbpipe(char *full_arg);
int		check_index_pipe(char *full_arg, int index_pipe);
t_cmd	*init_simple_struct(t_data *data, int index_pipe, t_cmd **cmd_pipe);
t_cmd	**init_struct_cmd(t_data *data);
t_cmd	*fill_simple_cmd(t_data *data, t_cmd *cmd, int i, int j);
int		init_file(t_cmd *res, t_data *data, int i);
int		check_command(char *str);
char	**sort_env(char **env);
void	init_null_cmd(t_cmd *res, int nb_cmd);
int		init_data(t_data *data, char **env);

//REMOVE_FIRST_ARGS
char	**remove_first_arg(t_data *data);
char	*remove_first_arg_in_full_arg(t_data *data);
void	remove_arg_if_needed(t_data *data);

//REDIRECTION
int		check_redirection(char *str);
int		reset_pipe_index_if_needed(char *full_arg);
int		check_only_redirection(char *str, char *full_arg);
int		size_here_doc_line(char *line, t_data *data);
void	here_doc(t_cmd *cmd, t_data *data);
void	here_doc_pipe(t_cmd *cmd, int **pipexfd, t_data *data, int i);
char	*tokenize_here_doc_limiter(char *str);
char	*fill_limiter(char *str, char *res);

//SIGNALS
void	catch_signal(int signal);
void	signal_handler(void);
void	ignore_signals(void);
void	unset_signals(void);

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
char	*ft_strjoin_no_malloc(char *s1, char *s2);

//CHECK_PATH
char	*check_path(char *cmd, char **env, t_data *data);

//CHECK_SYNTAX_ERROR
char	*check_syntax_error(char *str);
char	*check_here_doc(char *str, int *i);

//export_arg
int		check_size_export_arg(char *arg, int i);

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
int		size_tokenize(char *src, char **env, t_data *data);
char	**tokenizing(t_data *data);
int		check_quote(char *arg, int *i);
int		check_closing_quotes(char *s);
int		size_in_quote(char *str, int *i, int quote, t_data *data);
int		size_tokenize(char *src, char **env, t_data *data);
int		fill_tokenized_with_quote(t_data *data, char *res, char *src);
int		tokenize_arg(char *res, char *src, t_data *data);
int		size_env(char *str);
char	*isolate_env_var(char *cmd);
int		get_env_variable_size(char *cmd, char **envp, t_data *data);
int		fill_env(char *res, char *str, t_data *data, int *j);
char	*fill_exp(char *arg, char *res, int *i, int *j;);
int		count_size_exp(char *arg);
char	*alloc_export(char *arg, int *i);
int		fill_after_export(char **final_tab, char *arg, int *i, int *j);
int		check_export(char *str);
int		count_exp(char *str, int *i);

//BUILTIN
int		check_builtin(t_cmd *cmd, t_data *data);
int		check_builtin_pipe(t_cmd *cmd, int **pipexfd, t_data *data, int i);
int		check_echo_option(char *full_arg, char **cmd);
int		check_multiple_options(char *res);
int		check_option_format(char *full_arg, char *option);
int		is_valid_option(char **cmd, int cmd_i);
void	echo(char **cmd, t_data *data, int i, int arg_i);
void	pick_correct_echo(t_cmd *cmd, t_data *data);
void	echo_n(char **cmd, char *full_arg, int arg_i, int cmd_i);
int		move_cmd_arr_index(char **cmd, char *options);
char	*join_echo_options(char **cmd, char *full_arg);
char	*replace_env_in_full_arg(char *full_arg, t_data *data);
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
int		ft_strlen_var(char *str, t_data *data);

//PIPE
int		check_pipe(t_data *data);
void	dup_simple_call(t_cmd *cmd);
int		ft_pipe(t_data *data);
void	fi_pipe(t_data *data);
void	n_pipe(t_data *data, int i);
void	l_pipe(t_data *data, int i);
int		**malloc_pipe(int argc);
int		count_nb_here_doc(char **cmd);
void	check_dup_pipe_first(t_cmd *cmd, int **pipexfd, int i, t_data *data);
void	check_dup_pipe_n(t_cmd *cmd, int **pipexfd, int i, t_data *data);
void	check_dup_pipe_last(t_cmd *cmd, int **pipexfd, int i, t_data *data);

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
int		check_join_value(char *str);
char	*join_value_env(char *str, int line, char **env);

//UNSET
int		check_unset(char *str, char **env);
char	**new_tab(int i, char **src);

//FREE
void	free_parsing(t_data *data);
void	free_simple_cmd(t_cmd *cmd);
void	free_multiple_cmd(t_cmd **cmd);
void	clean_data(t_data *data, int trigger);
void	free_file(t_cmd *cmd);

//PARSING_HEREDOC
int		check_here_doc_null(char *str);
int		alloc_heredoc_null(char **final_tab, char *arg, int *line);
int		check_fill_heredoc_null(char **final_tab, char *arg, int *i, int *j);

//PARSING_RETURNVALUE
char	*fill_returnvalue(t_data *data, char *res, int *i);
int		replace_valuereturn(char *dest, int *j, t_data *data);
int		size_return_value(t_data *data);

//MOVE_INDEX
int		move_indextoenv(char *str, int i);
int		move_index_after_quote(char *str, int i);

#endif
