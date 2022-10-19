/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 10:44:27 by pirabaud          #+#    #+#             */
/*   Updated: 2022/10/19 03:40:34 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	init_file(t_cmd *res, t_data *data, int i)
{
	if (!res->type)
		free(res->type);
	res->type = ft_strdup(data->parsing[i]);
	if (!res->file)
		free(res->file);
	res->file = ft_strdup(data->parsing[i + 1]);
	if (check_open(&data->parsing[i]) == 1)
	{
		if (!res->cmd[0])
			ft_printf("minishell: %s: no such file or directory\n");
		else
			ft_printf("%s: %s: no such file or directory\n",
				res->cmd[0], res->file);
	}
}

char	**check_limiter(char **cmd)
{
	int		i;
	char	**res;
	int		j;

	i = 0;
	j = 0;
	while (cmd[i] != NULL)
	{
		if (ft_strcmp(cmd[i], "<<") == 0)
			++j;
		++i;
	}
	res = malloc((j + 1) * sizeof(char *));
	if (verif_malloc_arr(res) == 1)
		return (NULL);
	i = 0;
	j = 0;
	while (cmd[i] != NULL)
	{
		if (ft_strcmp(cmd[i], "<<") == 0)
			res[j++] = ft_strdup(cmd[i + 1]);
		++i;
	}
	res[j] = NULL;
	return (res);
}

t_cmd	*init_simple_cmd(t_data *data, int i, t_cmd *res)
{
	int		j;

	j = 0;
	res->cmd = malloc((nb_cmd(data->arg) + 1) * sizeof(char *));
	if (verif_malloc_arr(res->cmd) == 1)
		return (NULL);
	init_null_cmd(res);
	res->limiter = check_limiter(data->parsing);
	res = fill_simple_cmd(data, res, i, j);
	return (res);
}

t_cmd	*init_simple_struct(t_data *data, int index_pipe, t_cmd **cmd_pipe)
{
	t_cmd	*res;
	int		i;

	res = malloc(sizeof(t_cmd));
	if (verif_malloc_t_cmd(res, index_pipe, cmd_pipe) == 1)
		return (NULL);
	i = check_index_pipe(data->parsing, index_pipe);
	res = init_simple_cmd(data, i, res);
	if (!res->cmd)
		return (NULL);
	res->path = check_path(res->cmd[0], data->envp);
	if (!res->path && check_command(data->parsing[i]) != 1)
	{
		ft_printf("%s: command not found\n", res->cmd[0]);
		return (NULL);
	}
	return (res);
}

t_cmd	**init_struct_cmd(t_data *data)
{
	int		nb_pipe;
	int		i;
	t_cmd	**cmd_pipe;

	i = 0;
	nb_pipe = check_nbpipe(data->arg);
	cmd_pipe = malloc((nb_pipe + 1) * sizeof(t_cmd *));
	if (!cmd_pipe)
	{
		ft_putstr_fd("Malloc failed\n", 2);
		return (NULL);
	}
	while (nb_pipe > 0)
	{
		cmd_pipe[i] = init_simple_struct(data, i, cmd_pipe);
		if (!cmd_pipe[i])
			return (NULL);
		i++;
		nb_pipe--;
	}
	cmd_pipe[i] = NULL;
	return (cmd_pipe);
}
