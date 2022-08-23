/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 09:45:33 by blevrel           #+#    #+#             */
/*   Updated: 2022/08/23 15:15:55 by blevrel          ###   ########.fr       */
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
	parsing_arg(data);
	while (data->cmd[i])
	{
		if (check_quotes(data, i) == -1)
			return ;
		else if (check_quotes(data, i) == 1)
			modify_quotes(data, i);
		i++;
	}
	if (check_double_red(data) == 1)
		return ;
	if (check_redirection(data) == 1)
		return ;
	simple_cmd(data);
}

int	main(int argc, char **argv, char **env)
{
	int		run;
	t_data	data;
	int		i;

	run = 0;
	if (argc != 1)
	{
		printf("Program takes no arguments\n");
		return (0);
	}
	signal_handler();
	(void)argv;
	data.envp = dup_dp(env);
	while (run == 0)
	{
		i = 0;
		data.arg = readline("minishell ");
		if (data.arg && data.arg[0])
			add_history(data.arg);
		if (data.arg == NULL)
			exit(printf("\n"));
		init_cmd(&data);
		while (data.cmd[i])
		{
			printf("Valeur de data.cmd[%d] : %s\n", i, data.cmd[i]);
			i++;
		}
		if (data.arg)
			free(data.arg);
		if (data.cmd && data.cmd[0])
			free_cmd(&data);
	}
	return (0);
}
