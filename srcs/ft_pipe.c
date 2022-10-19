/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 20:48:40 by blevrel           #+#    #+#             */
/*   Updated: 2022/10/19 21:47:49 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	count_nb_here_doc(char **cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (ft_strcmp(cmd[i], "<<") == 0)
			count++;
		++i;
	}
	return (count);
}

void	wait_for_son(t_data *data, int j)
{
	while (data->son[j] != 0)
	{
		waitpid(data->son[j], NULL, 0);
		j++;
		g_signal_trigger = IN_COMMAND;
	}
}

int	ft_pipe(t_data *data)
{
	int		nb_pipe;
	int		i;
	int		j;

	i = 1;
	j = 0;
	nb_pipe = check_nbpipe(data->arg);
	if (!data->cmd)
		return (1);
	data->pipexfd = malloc_pipe(nb_pipe);
	data->son = malloc(nb_pipe * sizeof(int));
	if (!data->son)
		return (1);
	fi_pipe(data);
	while (nb_pipe > 2)
	{
		n_pipe(data, i);
		i++;
		nb_pipe++;
	}
	l_pipe(data, i);
	wait_for_son(data, j);
	return (0);
}
