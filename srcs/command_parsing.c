/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 09:45:33 by blevrel           #+#    #+#             */
/*   Updated: 2022/08/16 16:16:17 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	command_parsing(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		printf("cmd is %s\n", cmd);
	else if (ft_strcmp(cmd, "cd") == 0)
		printf("cmd is %s\n", cmd);
	else if (ft_strcmp(cmd, "pwd") == 0)
		printf("cmd is %s\n", cmd);
	else if (ft_strcmp(cmd, "export") == 0)
		printf("cmd is %s\n", cmd);
	else if (ft_strcmp(cmd, "unset") == 0)
		printf("cmd is %s\n", cmd);
	else if (ft_strcmp(cmd, "env") == 0)
		printf("cmd is %s\n", cmd);
	else if (ft_strcmp(cmd, "exit") == 0)
		printf("cmd is %s\n", cmd);
}

int	main(int argc, char **argv, char **env)
{
	int	run;

	run = 0;
	if (argc != 1)
	{
		printf("Program takes no arguments\n");
		return (0);
	}
	(void)argv;
	(void)env;
	char	*command;
	while (run == 0)
	{
		command = readline("minishell ");
		command_parsing(command);
	}
	return (0);
}
