/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:25:34 by blevrel           #+#    #+#             */
/*   Updated: 2022/10/28 10:43:00 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*tokenize_env_var(char *full_arg, char *res, t_data *data, int *i)
{
	char	*value;
	int		line;
	int		len_env;

	(*i)++;
	if (full_arg[*i] == '?')
		return (fill_returnvalue(data, res, i));
	value = isolate_env_var(&full_arg[*i]);
	line = 0;
	len_env = size_env(value);
	while (full_arg[*i] && check_char(&full_arg[*i]) == 0
		&& full_arg[*i] != '$')
		(*i)++;
	if (len_env == -1)
	{
		free(value);
		return (res);
	}
	while (data->envp[line] && ft_strncmp(data->envp[line], value, len_env + 1) != 0)
		line++;
	free(value);
	if (!data->envp[line])
		return (res);
	res = join_gnl(res, &data->envp[line][len_env + 1]);
	return (res);
}

char	*replace_env_in_quotes(char *full_arg, char *res, t_data *data, int *i)
{
	int	quote;
	int	j;

	quote = full_arg[*i];
	j = ft_strlen(res);
	res[j] = full_arg[*i];
	(*i)++;
	j++;
	while (full_arg[*i] && full_arg[*i] != quote)
	{
		if (full_arg[*i] == '$' && quote == 34)
		{
			res = tokenize_env_var(full_arg, res, data, i);
			j = ft_strlen(res);
		}
		else
		{
			res[j] = full_arg[*i];
			(*i)++;
			j++;
		}
	}
	if (full_arg[*i] == quote)
		(*i)++;
	return (res);
}

char	*replace_env_in_full_arg(char *full_arg, t_data *data)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = ft_calloc((ft_strlen_var(full_arg, data) + 1), sizeof(char));
	if (verif_malloc_str(&res, 0) == 1)
		return (NULL);
	while (full_arg[i])
	{
		if (check_char(&full_arg[i]) < 0
			&& check_closing_quotes(&full_arg[i]) == 0)
			res = replace_env_in_quotes(full_arg, res, data, &i);
		else if (full_arg[i] == '$' && full_arg[i + 1] != '$')
			res = tokenize_env_var(full_arg, res, data, &i);
		else
		{
			j = ft_strlen(res);
			ft_fill_char_and_increment(res, full_arg, &i, &j); 
		}
	}
	free(full_arg);
	full_arg = NULL;
	return (res);
}

int	move_arg_i_in_quote(char *full_arg, int arg_i)
{
	int	quote;

	quote = full_arg[arg_i - 1];
	while (full_arg[arg_i] != quote)
		arg_i++;
	arg_i++;
	while ((check_char(&full_arg[arg_i]) == 1)
		|| (check_char(&full_arg[arg_i]) < 0
			&& full_arg[arg_i] == full_arg[arg_i + 1]))
	{
		if (check_char(&full_arg[arg_i]) < 0
			&& full_arg[arg_i] == full_arg[arg_i + 1])
		{
			arg_i += 2;
			if (check_char(&full_arg[arg_i]) == 1)
				ft_printf(" ");
		}
		else
			arg_i++;
	}
	return (arg_i);
}

int	move_arg_i(char *full_arg, int arg_i)
{
	if (check_char(&full_arg[arg_i - 1]) < 0
		&& check_closing_quotes(&full_arg[arg_i - 1]) == 0)
		arg_i = move_arg_i_in_quote(full_arg, arg_i);
	else
	{
		while (full_arg[arg_i] && check_char(&full_arg[arg_i]) == 0)
			arg_i++;
		while ((check_char(&full_arg[arg_i]) == 1)
			|| (check_char(&full_arg[arg_i]) < 0
				&& full_arg[arg_i] == full_arg[arg_i + 1]))
		{
			if (check_char(&full_arg[arg_i]) < 0
				&& full_arg[arg_i] == full_arg[arg_i + 1])
			{
				arg_i += 2;
				if (check_char(&full_arg[arg_i]) == 1)
					ft_printf(" ");
			}
			else
				arg_i++;
		}
	}
	return (arg_i);
}
