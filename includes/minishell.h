/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 09:46:20 by blevrel           #+#    #+#             */
/*   Updated: 2022/08/22 14:06:30 by blevrel          ###   ########.fr       */
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

typedef struct	s_data
{
	char **envp;
	char **cmd;
	char *arg;
}	t_data;

void	simple_cmd(t_data *data);
void	entry_red(t_data *data);
void	exit_red(t_data *data);
char	*check_path(char *cmd, char **env);
void	catch_signal(int signal);
int		check_redirection(t_data *data);
void	here_doc(t_data *data);
int		check_double_red(t_data *data);
char	**check_arg(char **cmd, char c);
void	signal_handler(void);
int		ft_strchr_int(const char *s, int c);
void	*cmd_not_found(char *cmd);
void	append(t_data *data);
int		check_quotes(t_data *data, int i);
void	modify_quotes(t_data *data, int i);
void	modify_single_quotes(char *cmd, int len);
void	modify_double_quotes(char *cmd, int len);
char	check_last_non_spc_char(int i, char *str);
char	check_next_non_spc_char(int i, char *str);
int		check_char(char c);
void	parsing_arg(t_data *data);
void	free_double_tab(char **tab);
