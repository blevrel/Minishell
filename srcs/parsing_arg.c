/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 11:26:43 by blevrel           #+#    #+#             */
/*   Updated: 2022/08/24 17:18:34 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

//faire la difference entre ' et ", pour l'instant ca les traite de la meme facon
int	get_cmd_tab_size(char *arg)
{
	int		i;
	int		count;

	i = 0;
	count = 1;
	while ((arg[i] >= 9 && arg[i] <= 13) || arg[i] == ' ')
		i++;
	while (arg[i])
	{
		if (check_char(arg[i]) == -1 && count != 1)
			count += cmd_tab_size_quotes(&i, arg);
		if (check_char(arg[i]) == 1 && check_char(arg[i + 1]) < 1
			&& check_char(check_last_non_spc_char(i, arg)) <= 1 && arg[i + 1])
			count++;
		else if (check_char(arg[i]) == 2 && check_char(arg[i + 1]) <= 1)
		{
			if (arg[i + 1] && check_char(check_next_non_spc_char(i + 1, arg))
				<= 1)
				count++;
			count++;
		}
		i++;
	}
	return (count);
}

void	fill_cmd_tab(char *arg, char *cmd)
{
	static int	i = -1;
	int			j;
	int			trigger;

	j = 0;
	trigger = 0;
	i++;
	while ((arg[i] >= 9 && arg[i] <= 13) || arg[i] == ' ')
		i++;
	while (arg[i])
	{
		if (check_char(arg[i]) == -1)
		{
			fill_cmd_tab_with_quotes(&i, arg, cmd);
			return ;
		}
		if (trigger == 0 && (check_char(arg[i]) != check_char(arg[i + 1]) || !arg[i + 1]))
			trigger++;
		if (trigger != 0)
		{
			cmd[j] = arg[i];
			if (!arg[i + 1])
				i = -1;
			return ;
		}
		cmd[j] = arg[i];
		j++;
		i++;
	}
}

//faire la difference entre ' et ", pour l'instant ca les traite de la meme facon
void	allocate_cmd(char *arg, char **cmd)
{
	static int	i = -1;
	int			size;
	int			trigger;

	size = 0;
	trigger = 0;
	i++;
	while ((arg[i] >= 9 && arg[i] <= 13) || arg[i] == ' ')
		i++;
	while (arg[i])
	{
		if (check_char(arg[i]) == -1)
			size += allocate_cmd_with_quotes(&i, arg, &trigger);
		if ((trigger == 0 && ((check_char(arg[i]) != check_char(arg[i + 1]))
			|| !arg[i + 1])))
		{
			size++;
			trigger++;
		}
		if (trigger != 0)
		{
			printf("%d\n", size);
			*cmd = ft_calloc(sizeof(char), size + 1);
			fill_cmd_tab(arg, *cmd);
			if (!arg[i + 1])
				i = -1;
			return ;
		}
		size++;
		i++;
	}
}

void	parsing_arg(t_data *data)
{
	int	i;
	int	tab_size;

	i = 0;
	tab_size = get_cmd_tab_size(data->arg);
	data->cmd = ft_calloc(sizeof(char *), tab_size + 1);
	while (i < tab_size)
	{
		allocate_cmd(data->arg, &data->cmd[i]);
		if (!data->cmd[i])
			return ;
		i++;
	}
}
