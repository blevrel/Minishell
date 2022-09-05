/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 11:26:43 by blevrel           #+#    #+#             */
/*   Updated: 2022/09/05 11:38:16 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

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
		if (check_char(arg[i]) < 0)
			cmd_tab_size_quotes(&i, arg, arg[i]);
		if (check_char(arg[i]) == 1 && check_char(arg[i + 1]) < 1
			&& check_char(last_non_spc_char(i, arg)) <= 1 && arg[i + 1])
			count++;
		else if (check_char(arg[i]) == 2 && check_char(arg[i + 1]) <= 1)
		{
			if (arg[i + 1] && check_char(next_non_spc_char(i + 1, arg)) <= 1
				&& (check_char(last_non_spc_char(i - 1, arg)) <= 1
					|| check_char(last_diff_and_non_spc_char(i - 1, arg)) <= 1))
				count++;
			count++;
		}
		i++;
	}
	return (count);
}

void	share_cmd_tab(char *arg, char *cmd)
{
	static int	i = 0;
	int			trigger;

	trigger = 0;
	while ((arg[i] >= 9 && arg[i] <= 13) || arg[i] == ' ')
		i++;
	fill_cmd_tab(arg, &i, cmd, &trigger);
}

void	fill_cmd_tab(char *arg, int *i, char *cmd, int *trigger)
{
	int	j;

	j = 0;
	while (arg[*i])
	{
		if (check_char(arg[*i]) == 1)
			fill_cmd_space(arg, i, trigger);
		else if (check_char(arg[*i]) == 2)
		{
			fill_cmd_redirection(arg, i, cmd, &j);
			*trigger = 1;
		}
		else if (check_char(arg[*i]) < 0)
		{
			fill_cmd_quotes(arg, i, &cmd[j], arg[*i]);
			*trigger = 1;
		}
		else
			cmd[j] = arg[*i];
		if (*trigger == 1)
			return ;
		*i += 1;
		j++;
	}
	*i = 0;
}

void	allocate_cmd(char *arg, char **cmd, int tab_size)
{
	static int	i = 0;
	int			size;

	size = 0;
	while ((arg[i] >= 9 && arg[i] <= 13) || arg[i] == ' ')
		i++;
	if (tab_size == 1)
	{
		*cmd = ft_strdup(&arg[i]);
		if (!*cmd)
			return ;
		return ;
	}
	size = alloc_multitab(arg, &i, &size);
	*cmd = ft_calloc(sizeof(char), size + 1);
	if (!*cmd)
		return ;
	share_cmd_tab(arg, *cmd);
}

int	alloc_multitab(char *arg, int *i, int *size)
{
	static int	not_first_arg = 0;
	int			trigger;

	trigger = 0;
	while (arg[*i])
	{
		if (check_char(arg[*i]) == 1)
			*size += parsing_with_space(arg, i, &not_first_arg, &trigger);
		else if (check_char(arg[*i]) == 2)
		{
			*size += parsing_with_redirection(arg, i, &not_first_arg, *size);
			trigger = 1;
		}
		else if (check_char(arg[*i]) < 0)
		{
			*size += parsing_with_quotes(arg, i, &not_first_arg, arg[*i]);
			trigger = 1;
		}
		else
			*size += 1;
		if (trigger == 1)
			return (*size);
		*i += 1;
	}
	return (reset_statics(i, &not_first_arg, *size));
}
