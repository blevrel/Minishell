/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 09:45:33 by blevrel           #+#    #+#             */
/*   Updated: 2022/08/27 14:34:27 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	free_cmd(t_data *data)
{
	int	i;

	i = 0;
	while (data->cmd[i])
	{
		free(data->cmd[i]);
		i++;
	}
	free(data->cmd);
}

void	init_cmd(t_data *data)
{
	int	i;

	i = 0;
	if (!data->arg)
		return ;
	if (ft_strchr_int(data->arg, 34) % 2 == 1 || ft_strchr_int(data->arg, 39)
		% 2 == 1)
	{
		printf("Missing quote\n");
		return ;
	}
	parsing_arg(data);
	while (data->cmd[i])
	{
		if (check_quotes(data, i) == -1)
			return ;
		else if (check_quotes(data, i) == 1)
			modify_quotes(data, i);
		i++;
	}
	if (check_pipe(data) == 1)
		return ;
	if (check_double_red(data) == 1)
		return ;
	if (check_redirection(data) == 1)
		return ;
	if (simple_cmd(data) == 1)
		cmd_not_found(data->cmd[0]);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	if (argc != 1)
	{
		printf("Program takes no arguments\n");
		return (0);
	}
	signal_handler();
	(void)argv;
	data.envp = dup_dp(env);
	while (1)
	{
		data.arg = readline("Mishell->");
		if (data.arg && data.arg[0])
			add_history(data.arg);
		if (data.arg == NULL)
			exit(printf("\n"));
		init_cmd(&data);
		if (data.arg)
			free(data.arg);
		if (data.cmd && data.cmd[0])
			free_cmd(&data);
	}
	return (0);
}
