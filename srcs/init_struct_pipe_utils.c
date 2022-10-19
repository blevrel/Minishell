/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_pipe_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 09:47:41 by pirabaud          #+#    #+#             */
/*   Updated: 2022/10/19 22:05:17 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	check_nbpipe(char *full_arg)
{
	int	res;
	int	i;
	int	quote;

	i = 0;
	res = 1;
	while (full_arg[i])
	{
		if (check_char(&full_arg[i]) < 0)
		{
			quote = full_arg[i];
			i++;
			while (full_arg[i] != quote)
				i++;
			i++;
		}
		if (full_arg[i] == '|')
			res++;
		i++;
	}
	return (res);
}

int	check_index_pipe(char *full_arg, int index_pipe)
{
	static int	i = 0;
	int			count;

	if (index_pipe == 0)
		return (0);
	count = nb_cmd(&full_arg[i]);
	while (full_arg[i] && full_arg[i] != '|')
	{
		if (check_char(&full_arg[i]) < 0)
			i = move_index_after_quote(full_arg, i + 1, full_arg[i]);
		else
			i++;
	}
	if (reset_pipe_index_if_needed(&full_arg[i + 1]) == 0)
		i = 0;
	return (count + 1);
}

int	nb_cmd(char *full_arg)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (full_arg[i] && full_arg[i] != '|')
	{
		while (full_arg[i] && check_char(&full_arg[i]) == 1)
			i++;
		if (full_arg[i] && check_char(&full_arg[i]) == 2)
			res++;
		while (check_char(&full_arg[i]) == 2)
				i++;
		if (full_arg[i] && check_char(&full_arg[i]) == 0 && full_arg[i] != '|')
			res++;
		while (full_arg[i] && check_char(&full_arg[i]) == 0)
			i++;
		if (check_char(&full_arg[i]) < 0)
		{
			i = move_index_after_quote(full_arg, i + 1, full_arg[i]);
			res++;
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

t_cmd	*fill_simple_cmd(t_data *data, t_cmd *res, int i, int j)
{
	int	value;

	while (data->parsing[i] != NULL)
	{
		value = check_only_redirection(data->parsing[i], data->arg);
		if (value == 1)
		{
			init_file(res, data, i);
			if (data->parsing[i + 1])
				i = i + 2;
			else
				i++;
		}
		else if (value == 2)
			break ;
		else
		{
			res->cmd[j] = ft_strdup(data->parsing[i]);
			j++;
			i++;
		}
	}
	res->cmd[j] = NULL;
	return (res);
}
