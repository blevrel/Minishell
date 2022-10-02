/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenized_quotes_size.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:58:46 by blevrel           #+#    #+#             */
/*   Updated: 2022/10/01 17:55:28 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	get_quote_modif_size(char *cmd, char **envp, int *i)
{
	int	size;

	size = 0;
	while (cmd[*i])
	{
		if (cmd[*i] == 34)
		{
			size = get_double_quote_size(cmd, i, envp);
			return (size);
		}
		else if (cmd[*i] == 39)
		{
			size = get_single_quote_size(cmd, i);
			return (size);
		}
	}
	return (size);
}

int	get_single_quote_size(char *cmd, int *i)
{
	int	size;
	int	quote;

	size = 0;
	quote = 0;
	(*i)++;
	while (cmd[*i])
	{
		if (cmd[*i] == 39)
			quote = 1;
		if (cmd[*i] == 39 && cmd[*i - 1] == 39 && cmd[*i - 2] == 39)
		{
			quote = 0;
			(*i)++;
			continue ;
		}
		if (quote == 1)
			break ;
		size++;
		(*i)++;
	}
	(*i)++;
	return (size);
}

int	get_double_quote_size(char *cmd, int *i, char **envp)
{
	int	size;
	int	quote;

	size = 0;
	quote = 0;
	(*i)++;
	while (cmd[*i])
	{
		if (cmd[*i] == 34)
			quote = 1;
		if (cmd[*i] == 34 && cmd[*i - 1] == 34 && cmd[*i - 2] == 34)
		{
			quote = 0;
			(*i)++;
			continue ;
		}
		if (quote == 1)
			break ;
		if (cmd[*i] == '$')
		{
			size += get_env_variable_size(&cmd[*i + 1], envp);
			(*i)++;
			continue ;
		}
		else
			size++;
		(*i)++;
	}
	(*i)++;
	return (size);
}
