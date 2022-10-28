/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 10:45:41 by blevrel           #+#    #+#             */
/*   Updated: 2022/09/27 15:08:41 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	print_exit_error(int trigger, char *arg)
{
	(void)arg;
	if (trigger == 0)
	{
		printf("exit\n");
		return (ft_atoi(arg));
	}
	if (trigger == 1)
	{
		printf("exit\n");
		printf("minishell: exit: %s: numeric argument required\n", arg);
		return (0);
	}
	if (trigger == 2)
	{
		printf("exit\n");
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	return (-1);
}

void	ft_exit(t_data *data)
{
	int	exit_arg;
	int	exit_value;

	exit_arg = 0;
	if (data->parsing[1])
		check_exit_arg(data->parsing, &exit_arg);
	else
	{
		free_parsing(data);
		free(data->arg);
		free_double_tab(data->export);
		free_double_tab(data->envp);
		free(data);
		printf("exit\n");
		exit(0);
	}
	exit_value = print_exit_error(exit_arg, data->parsing[1]);
	if (exit_value == 1 && data->parsing[2])
		return ;
	free(data->arg);
	free_double_tab(data->export);
	free_double_tab(data->envp);
	free_parsing(data);
	free(data);
	exit(exit_value);
}

void	check_exit_arg(char **args, int *exit_arg)
{
	int	i;

	i = 0;
	while (args[1][i])
	{
		if (ft_isdigit(args[1][i]) == 2048)
			i++;
		else
		{
			*exit_arg = 1;
			if (!args[2])
				return ;
			break ;
		}
	}
	if (args[2] && *exit_arg == 0)
	{
		*exit_arg = 2;
		return ;
	}
}
