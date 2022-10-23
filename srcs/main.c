/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 09:45:33 by blevrel           #+#    #+#             */
/*   Updated: 2022/10/18 22:07:19 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	**remove_first_arg(t_data *data)
{
	int		i;
	char	**new_parsing_tab;

	i = 0;
	if (data->parsing[0][0])
		return (data->parsing);
	new_parsing_tab = ft_calloc(sizeof(char *), size_tab(data->parsing));
	if (verif_malloc_arr(new_parsing_tab) == 1)
		return (NULL);
	while (data->parsing[i + 1])
	{
		new_parsing_tab[i] = ft_strdup(data->parsing[i + 1]);
		i++;
	}
	free_double_tab(data->parsing);
	return (new_parsing_tab);
}

void	init_cmd(t_data *data)
{
	data->arg = check_syntax_error(data->arg);
	if (data->arg == NULL)
		return ;
	data->parsing = alloc_final_tab(data);
	if (!data->parsing || data->parsing[0]== NULL)
		return ;
	data->parsing = tokenizing(data);
	if (next_non_spc_char(0, data->arg) != 34
		&& next_non_spc_char(0, data->arg) != 39)
		data->parsing = remove_first_arg(data);
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
			ft_printf("exit\n");
			exit(0);
		}
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
		ft_putstr_fd("Malloc failed", 2);
		return (0);
	}
	init_data(data, env);
	routine(data);
	return (0);
}
