/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 09:45:33 by blevrel           #+#    #+#             */
/*   Updated: 2022/10/28 10:22:40 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	init_cmd(t_data *data)
{
	data->arg = check_syntax_error(data->arg);
	if (data->arg == NULL)
		return ;
	data->parsing = alloc_final_tab(data);
	if (!data->parsing || !data->parsing[0])
		return ;
	data->parsing = tokenizing(data);
	if (next_non_spc_char(0, data->arg) != 34
		&& next_non_spc_char(0, data->arg) != 39)
		remove_arg_if_needed(data);
	if (ft_strcmp(data->parsing[0], "exit") == 0)
	{
		ft_exit(data);
		return ;
	}
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
		{
			free(data->arg);
			free_double_tab(data->export);
			free_double_tab(data->envp);
			free(data);
			ft_printf("exit\n");
			exit(0);
		}
		if (data->arg[0])
			init_cmd(data);
		clean_data(data, 0);
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
		ft_putstr_fd("Malloc failed", 2);
		return (0);
	}
	if (init_data(data, env) == 1)
		return (0);
	routine(data);
	ft_printf("exit\n");
	free_double_tab(data->envp);
	free_double_tab(data->export);
	free(data);
	return (0);
}
