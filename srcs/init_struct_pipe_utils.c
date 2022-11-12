/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_pipe_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 09:47:41 by pirabaud          #+#    #+#             */
/*   Updated: 2022/11/12 15:40:01 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

//mettre la boucle index_pipe = 0 dans une autre fonction
int	check_index_pipe(char *full_arg, int index_pipe)
{
	static int	i = 0;
	int			count;

	if (full_arg[i] == '|')
		i++;
	if (index_pipe == 0)
	{
		while (full_arg[i] && full_arg[i] != '|')
		{
			if (check_char(&full_arg[i]) < 0)
				i = move_index_after_quote(full_arg, i);
			else
				i++;
		}
		if (reset_pipe_index_if_needed(&full_arg[i]) == 0)
			i = 0;
		return (0);
	}
	count = nb_cmd(full_arg, index_pipe);
	while (full_arg[i] && full_arg[i] != '|')
	{
		if (check_char(&full_arg[i]) < 0)
			i = move_index_after_quote(full_arg, i + 1);
		else
			i++;
	}
	if (reset_pipe_index_if_needed(&full_arg[i]) == 0)
		i = 0;
	return (count);
}

int	check_open(char **cmd)
{
	int	fd;

	if (ft_strcmp(cmd[0], ">") == 0)
	{
		fd = open(cmd[1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd == -1)
			return (1);
		close (fd);
	}
	if (ft_strcmp(cmd[0], ">>") == 0)
	{
		fd = open(cmd[1], O_WRONLY | O_APPEND | O_CREAT, 0644);
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
	//else
		//here_doc(limiter, data);
	return (0);
}

t_cmd	*fill_simple_cmd(t_data *data, t_cmd *res, int i, int j)
{
	int			value;
	static int	trigger = 0;

	while (data->parsing[i] != NULL)
	{
		value = get_arg_type(data, data->parsing[i], data->arg, trigger);
		if (value == 1)
		{
			if (init_file(res, data, i) == 1)
			{
				trigger = 0;
				return (res);
			}
			if (data->parsing[i + 1])
				i++;
		}
		else if (value == 2)
			break ;
		else if (value != 1 /*&& ft_strcmp(data->parsing[i], "") != 0*/)
			res->cmd[j++] = ft_strdup(data->parsing[i]);
		trigger++;
		i++;
	}
	res->cmd[j] = NULL;
	trigger = 0;
	return (res);
}
