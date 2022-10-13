/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_pipe_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 09:47:41 by pirabaud          #+#    #+#             */
/*   Updated: 2022/10/13 20:28:17 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirection(char *str)
{
	if (ft_strncmp(str, "<", 1) == 0)
		return (1);
	else if (ft_strncmp(str, ">", 1) == 0)
		return (1);
	else if (ft_strncmp(str, ">>", 2) == 0)
		return (1);
	else if (ft_strncmp(str, "<<", 2) == 0)
		return (1);
	else if (ft_strncmp(str, "|", 1) == 0)
		return (2);
	else
		return (0);
}

int	check_nbpipe(char **argv)
{
	int	res;
	int	i;

	i = 0;
	res = 1;
	while (argv[i] != NULL)
	{
		if (ft_strcmp(argv[i], "|") == 0)
			++res;
		++i;
	}
	return (res);
}

int	check_index_pipe(char **argv, int index_pipe)
{
	int	nb_pipe;
	int	i;

	i = 0;
	nb_pipe = 0;
	while (argv[i] != NULL && nb_pipe != index_pipe)
	{
		++i;
		if (ft_strcmp(argv[i], "|") == 0)
			nb_pipe++;
	}
	if (nb_pipe != 0)
		++i;
	return (i);
}

int	nb_cmd(char **argv, int i)
{
	int	res;

	res = 0;
	while (argv[i] != NULL && ft_strcmp(argv[i], "|"))
	{
		if (check_redirection(argv[i]) == 1 && ft_strcmp(argv[i], "<<") == 0)
		{
			if (argv[i + 1])
				i = i + 2;
			else
				i++;
		}
		else
		{
			++i;
			++res;
		}
	}
	return (res);
}

int	check_open(char **cmd)
{
	int	fd;

	if (ft_strcmp(cmd[0], ">") == 0)
	{
		fd = open(cmd[1], O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
		if (fd == -1)
			return (1);
		close (fd);
	}
	if (ft_strcmp(cmd[0], ">>") == 0)
	{
		fd = open(cmd[1], O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
		if (fd == -1)
			return (1);
		close (fd);
	}
	if (ft_strcmp(cmd[0], "<") == 0)
	{
		fd = open(cmd[1], O_RDONLY);
		if (fd == -1)
			return (1);
		close (fd);
	}
	return (0);
}
