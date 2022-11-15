/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 10:45:41 by blevrel           #+#    #+#             */
/*   Updated: 2022/11/15 14:07:17 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	print_exit_error(int trigger, char *arg, int return_value)
{
	if (!arg)
		return (return_value);
	if (trigger == 0)
	{
		printf("exit\n");
		return (ft_atoi(arg));
	}
	if (trigger == 1)
	{
		printf("exit\n");
		ft_print_error("minishell: exit: %s: Numeric argument required\n", arg);
		return (2);
	}
	if (trigger == 2)
	{
		printf("exit\n");
		ft_print_error("minishell: exit: Too many arguments\n");
		return (1);
	}
	return (-1);
}

void	ft_exit(t_data *data)
{
	int	exit_arg;
	int	exit_val;

	exit_arg = 0;
	if (data->parsing[1])
		exit_arg = check_exit_arg(data->parsing);
	else
		printf("exit\n");
	exit_val = print_exit_error(exit_arg, data->parsing[1], data->return_value);
	if (exit_val == 1 && data->parsing[2])
	{
		data->return_value = 1;
		return ;
	}
	free(data->arg);
	free_double_tab(data->export);
	free_double_tab(data->envp);
	free_parsing(data);
	free(data);
	exit(exit_val);
}

int	check_exit_arg(char **args)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (args[1][i] && res != 1 && i < 18)
	{
		if (i == 0 && (args[1][i] == '-' || args[1][i] == '+'))
			i++;
		else if (ft_isdigit(args[1][i]) == 2048)
			i++;
		else
			res = 1;
	}
	if (i >= 18)
		res = 1;
	if (args[2] && res == 0)
		res = 2;
	return (res);
}
