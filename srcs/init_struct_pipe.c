/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 10:44:27 by pirabaud          #+#    #+#             */
/*   Updated: 2022/09/20 09:55:55 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_null_cmd(t_cmd *res)
{
	res->type = NULL;
	res->file = NULL;
}

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
			ft_printf("%s: %s: no such file or directory\n", res->cmd[0], res->file);
	}
		
}

char 	**check_limiter(char **cmd)
{
	int	i;
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
	if (!res)
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

void	init_simple_cmd(t_data *data, t_cmd *res, int i)
{
	int	j;

	j = 0;
	res->cmd = malloc((nb_cmd(data->parsing, i) + 1) * sizeof(char *));
	if (!res->cmd)
	{
		ft_putstr_fd("error malloc", 2);
		return ;
	}
	init_null_cmd(res);
	res->limiter = check_limiter(data->parsing);
	while (data->parsing[i] != NULL && ft_strcmp(data->parsing[i], "|"))
	{
		if (check_redirection_pipe(data->parsing[i]) == 1)
		{
			init_file(res, data, i);
			i = i + 2;
		}
		else
			res->cmd[j++] = ft_strdup(data->parsing[i++]);
	}
	res->cmd[j] = NULL;
}

t_cmd	*init_simple_struct(t_data *data, int index_pipe)
{
	t_cmd	*res;
	int		i;

	i = check_index_pipe(data->parsing, index_pipe);
	res = malloc(sizeof(t_cmd));
	init_simple_cmd(data, res, i);
	if (!res->cmd)
		return (NULL);
	return (res);
}

t_cmd	**init_struct_cmd(t_data *data)
{
	int		nb_pipe;
	int		i;
	t_cmd	**cmd_pipe;

	i = 0;
	
	nb_pipe = check_nbpipe(data->parsing);
	cmd_pipe = malloc((nb_pipe + 1) * sizeof(t_cmd *));
	if (!cmd_pipe)
	{
		ft_putstr_fd("error malloc\n", 2);
		return (NULL);
	}
	while (nb_pipe > 0)
	{
		cmd_pipe[i] = init_simple_struct(data, i);
		if (cmd_pipe[i] == NULL)
			return (NULL);
		cmd_pipe[i]->path = check_path(cmd_pipe[i]->cmd[0], data->envp);
		if(!cmd_pipe[i]->path && check_redirection_pipe(cmd_pipe[i]->cmd[0]) != 1)
		{
			ft_printf("%s : command not found\n", cmd_pipe[i]->cmd[0]);
			return (NULL);
		}
		i++;
		--nb_pipe;
	}
	cmd_pipe[i] = NULL;
	return (cmd_pipe);
}
