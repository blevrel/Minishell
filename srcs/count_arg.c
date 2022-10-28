/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:32:51 by pirabaud          #+#    #+#             */
/*   Updated: 2022/10/26 11:37:29 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	go_to_first_arg(char *arg, int *i)
{
	int	count;
	int	quote;

	count = 0;
	while (check_char(&arg[*i]) == 2)
	{
		(*i)++;
		if (check_char(&arg[*i]) != 2)
			return (1);
	}
	while (arg[*i] && (check_char(&arg[*i]) <= 0))
	{	
		if (check_char(&arg[*i]) < 0)
		{
			quote = arg[(*i)++];
			while (arg[*i] && arg[*i] != quote)
					(*i)++;
		}
		count++;
		if (arg[*i])
			(*i)++;
	}
	if (count <= 0)
		return (0);
	return (1);
}

int	check_here_doc_null(char *str)
{
	int	i;
	int	res;
	
	i = 0;
	res = 0;
	while(str[i] == '<')
		i++;
	if (str[i] == '"' && str[i + 1] == '"')
	{
		i = i + 2;
		res = 1;
	}
	if (res == 1 && (check_char(&str[i]) != 0 || str[i] == 0))
		return (1);
	return (0);
}

int	count_arg(char *arg, int *i)
{
	int	res;

	res = 0;
	while (arg[*i] && arg[*i] != '|')
	{
		while (arg[*i] && check_char(&arg[*i]) == 1)
			(*i)++;
		if (arg[*i] && check_char(&arg[*i]) == 2)
		{
			if(check_here_doc_null(&arg[*i]) == 1)
				res++;
			res++;
		}
		while (check_char(&arg[*i]) == 2)
				(*i)++;
		if (arg[*i] && check_char(&arg[*i]) == 0 && arg[*i] != '|')
		{
			while (arg[*i] && check_char(&arg[*i]) == 0)
				(*i)++;
			res++;
		}
		res += check_quote(arg, i);
	}
	return (res);
}

int	check_export(char *str)
{
	int		i;
	int		j;
	char	*check;

	i = 0;
	j = 0;
	check = malloc(7 * sizeof(char));
	if (!check)
	{
		ft_putstr_fd("malloc failed\n", 2);
		return (0);
	}
	while (str[i] && j < 6)
	{
		if (check_char(&str[i]) >= 0)
			check[j++] = str[i];
		++i;
	}
	check[j] = 0;
	if (ft_strncmp(check, "export", 6) == 0)
	{
		free(check);
		return (1);
	}
	free(check);
	return (0); 
}

int	count_exp(char *arg, int *i)
{
	int	res;
	
	res = 0;
	while (arg[*i] && (check_char(&arg[*i]) <= 0))
		res += go_to_first_arg(arg, i);
	return (res);
}

int	nb_arg(char *arg)
{
	int	i;
	int	res;
	int	check_exp;

	res = 0;
	i = 0;
	check_exp = 0;
	while (arg[i])
	{
		while (arg[i] && check_char(&arg[i]) == 1)
			i++;
		check_exp = check_export(&arg[i]);
		res += go_to_first_arg(arg, &i);
		while (arg[i] && check_char(&arg[i]) == 1)
			i++;
		if (arg[i] == '|')
		{
			while (arg[i] == '|')
				i++;
			res++;
		}
		if (check_exp == 1)
			res += count_exp(arg, &i);
		if (res != 0 && arg[i])
			res += count_arg(arg, &i);
	}
	return (res);
}

int	count_size_first_arg(char *arg)
{
	int	i;
	int	res;
	int	quote;

	i = 0;
	res = 0;
	quote = 0;
	while (arg[i] && check_char(&arg[i]) == 1)
		i++;
	while (arg[i] && (check_char(&arg[i]) == 2))
	{
		++i;
		++res;
	}
	while (arg[i] && check_char(&arg[i]) <= 0)
	{
		if (check_char(&arg[i]) < 0)
		{
			quote = arg[i];
			i++;
			res++;
			while (arg[i] != quote)
			{
				res++;
				i++;
			}
		}
		i++;
		res++;
	}
	return (res);
}

int	count_size_exp(char *arg)
{
	int	i;
	int	res;
	int	quote;

	i = 0;
	res = 0;
	quote = 0;
	while (arg[i] && check_char(&arg[i]) == 1)
		i++;
	while (arg[i] && (check_char(&arg[i]) <= 0))
	{
		if (check_char(&arg[i]) < 0)
		{
			quote = arg[i];
			while (arg[++i] != quote)
				res++;
		}
		i++;
		res++;
	}
	return (res);
}

int	count_size_arg(char *arg, int value)
{
	int	i;

	i = 0;
	while (arg[i] && check_char(&arg[i]) == value)
		i++;
	return (i);
}
