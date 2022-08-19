/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 09:45:33 by blevrel           #+#    #+#             */
/*   Updated: 2022/08/19 18:08:52 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	size_tab(char **str)
{
	int	i;
	
	i = 0;
	while (str[i] != NULL)
		++i;
	return (i - 1);
}

int		init_cmd(t_data data)
{
	data.cmd = ft_split(data.arg, ' ');
	if (!data.cmd || !data.cmd[0])
		return (1);
	if (check_double_red(data) == 1)
		return (1);
	if	(check_redirection(data) == 1)
		return (1);
	simple_cmd(data);
	
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	int	run;
	t_data	data;

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
		data.arg = readline("minishell ");
		if (data.arg && data.arg[0])
			add_history(data.arg);
		if (data.arg == NULL)
			exit(printf("\n"));
		init_cmd(data);
		free(data.arg);
	}
	return (0);
}
