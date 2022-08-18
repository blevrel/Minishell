/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 09:45:33 by blevrel           #+#    #+#             */
/*   Updated: 2022/08/18 10:36:15 by pirabaud         ###   ########.fr       */
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

int	check_redirection(t_data data)
{
	int	i;

	i = 0;
	while (data.cmd[i] != NULL)
	{
		if (ft_strcmp(data.cmd[i], ">") == 0)
		{
			entry_red(data);
			return (1);
		}
		if (ft_strcmp(data.cmd[i], ">") == 0)
		{
			exit_red(data);
			return (1);
		}
		i++;
	}		
	return (0);
}

int		init_cmd(t_data data)
{
	data.cmd = ft_split(data.arg, ' ');
	if (data.cmd == NULL)
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
	(void)argv;
	data.envp = dup_dp(env);
	while (run == 0)
	{
		data.arg = readline("minishell ");
		init_cmd(data);
		free(data.arg);
	}
	return (0);
}
