/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 09:45:33 by blevrel           #+#    #+#             */
/*   Updated: 2022/09/27 09:57:03 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	free_parsing(t_data *data)
{
	int	i;

	i = 0;
	while (data->parsing[i])
	{
		free(data->parsing[i]);
		data->parsing[i] = NULL;
		i++;
	}
	free(data->parsing);
	data->parsing = NULL;
}
void	free_simple_cmd(t_cmd *cmd)
{
	int	j;

	j = 0;
	if (cmd->path)
		free(cmd->path);
	cmd->path = NULL;
	if (cmd->type)
		free(cmd->type);
	cmd->type = NULL;
	if (cmd->file)
		free(cmd->file);
	cmd->file = NULL;
	while(cmd->limiter[j])
			free(cmd->limiter[j++]);
	free(cmd->limiter);
	cmd->limiter = NULL;
	j = 0;
	while(cmd->cmd[j])
			free(cmd->cmd[j++]);
	free(cmd->cmd);
	cmd->cmd = NULL;
}
void	free_multiple_cmd(t_data *data)
{
	int	i;
	
	i = 0;
	while (data->cmd[i] != NULL)
	{
		free_simple_cmd(data->cmd[i]);
		free(data->cmd[i]);
		data->cmd[i] = NULL;
		++i;
	}
	free(data->cmd);
	data->cmd = NULL;
}

void	free_data(t_data *data)
{
	if (data->parsing && data->parsing[0])
			free_parsing(data);
	free(data->arg);
	free(data->son);
	data->arg = NULL;
	data->son = NULL;
	if (data->cmd)
		free_multiple_cmd(data);
}

void	init_cmd(t_data *data)
{
	if (check_closing_quotes(data->arg) == 1)
	{
		printf("Missing_quote\n");
		return ;
	}
	parsing_arg(data);
	if (!data)
		return ;
	tokenize(data);
	data->cmd = init_struct_cmd(data);
	if (data->cmd == NULL)
		return ;
	if (check_pipe(data) == 1)
		return ;
	simple_cmd(data);
	
}
void	init_data(t_data *data, char **env)
{
	data->envp = dup_dp(env);
	data->export = dup_dp(env);
	data->export = sort_env(data->export);
	data->parsing = NULL;
	data->tokenized_str = NULL;
	data->arg = NULL;
	data->son = NULL;
	data->cmd = NULL;
	data->pipexfd = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_data *data;

	if (argc != 1)
	{
		printf("Program takes no arguments\n");
		return (0);
	}
	signal_handler();
	(void)argv;
	data = malloc(sizeof(t_data));
	if (!data)
	{
		ft_putstr_fd("error malloc", 2);
		return (0);
	}
	init_data(data, env);
	while (1)
	{
		data->arg = readline("Mishell-> ");
		if (data->arg && data->arg[0])
			add_history(data->arg);
		if (data->arg == NULL)
			exit(printf("\n"));
		if (data->arg[0])
			init_cmd(data);
		free_data(data);
	}
	return (0);
}
