/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 10:44:27 by pirabaud          #+#    #+#             */
/*   Updated: 2022/09/08 17:46:12 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_redirection_pipe(char *str)
{
	if (ft_strcmp(str, "<") == 0)
		return (1);
	else if (ft_strcmp(str, ">") == 0)
		return (1);
	else if (ft_strcmp(str, "<<") == 0)
		return (1);
	else if (ft_strcmp(str, ">>") == 0)
		return (1);
	else
		return (0);
}

int	check_nbpipe(char **argv)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	while (argv[i] != NULL)
	{
		if (ft_strcmp(argv[i], "|") == 0)
			++res;
		++i;
	}
	return (res);
}

static int	check_index_pipe(char **argv, int index_pipe)
{
	int	nb_pipe;
	int	i;

	i = 0;
	nb_pipe = 0;
	while (argv[i] != NULL && nb_pipe != index_pipe)
	{
		++i;
		if (ft_strcmp(argv[i], "|"))
			nb_pipe++;
	}
	return (i);
}

static int	nb_cmd(char **argv, int i)
{
	int	res;

	res = 0;
	while (argv[i] != NULL && ft_strcmp(argv[i], "|"))
	{
		if (check_redirection_pipe(argv[i]) == 1)
			i = i + 2;
		else
		{
			++i;
			++res;
		}
	}
	return (res);
}

t_cmd	*init_cmd_pipe(t_data *data, int index_pipe)
{
	t_cmd	*res;
	int		i;

	i = check_index_pipe(data->cmd, index_pipe);
	res = malloc(sizeof(t_cmd));
	res->cmd = malloc((nb_cmd(data->cmd, i) + 1) * sizeof(char *));
	if (!res->cmd)
	{
		ft_putstr_fd("error malloc", 2);
		return (NULL);
	}
	while (data->cmd[i] != NULL && ft_strcmp(data->cmd[i], "|"))
	{
		if (!res->type && check_redirection_pipe(data->cmd[i]) == 1)
		{
			res->type = ft_strdup(data->cmd[i]);
			res->file = ft_strdup(data->cmd[i + 1]);
			i = i + 2;
		}
		else
		{
			res->cmd[i] = ft_strdup(data->cmd[i]);
			i++;
		}
		res->cmd[i] = NULL;
	}
	return (res);
}

t_cmd	**init_struct_pipe(t_data *data)
{
	int		nb_pipe;
	int		i;
	t_cmd	**cmd_pipe;

	i = 0;
	nb_pipe = check_nbpipe(data->cmd);
	cmd_pipe = malloc((nb_pipe + 1) * sizeof(t_cmd *));
	if (!cmd_pipe)
	{
		ft_putstr_fd("error malloc", 2);
		return (NULL);
	}
	while (nb_pipe > 0)
	{
		cmd_pipe[i] = init_cmd_pipe(data, i);
		cmd_pipe[i]->path = check_path(cmd_pipe[i]->cmd[0], data->envp);
		i++;
		--nb_pipe;
	}
	return (cmd_pipe);
}
