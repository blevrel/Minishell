/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 09:45:33 by blevrel           #+#    #+#             */
/*   Updated: 2022/09/27 15:17:17 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

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

void	routine(t_data *data)
{
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
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

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
	routine(data);
	return (0);
}
