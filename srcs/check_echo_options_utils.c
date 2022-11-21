/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_echo_options_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 00:03:37 by blevrel           #+#    #+#             */
/*   Updated: 2022/11/21 14:41:33 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_strlen_var(char *str, t_data *data)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	if (!str)
		return (res);
	while (str[i])
	{
		if (str[i] == '$' && (ft_isalnum(str[i + 1]) == 8 || str[i + 1] == '?'))
		{
			res += get_env_variable_size(&str[i], data->envp, data);
			i++;
			while (str[i] && ((ft_isalnum(str[i]) == 8 && (str[i - 1] != '?'))
					|| (str[i] == '?' && str[i - 1] == '$')))
				i++;
		}
		else
		{
			i++;
			res++;
		}
	}
	return (res);
}

char	*ft_strjoin_no_malloc(char *s1, char *s2)
{
	int		i;
	int		j;

	i = 0;
	if (!s1)
		return (NULL);
	if (!s2)
		return (NULL);
	j = ft_strlen(s1);
	while (s2[i])
		ft_fill_char_and_increment(s1, s2, &i, &j);
	return (s1);
}

int	check_option_format_in_quotes(char *full_arg, int *j, char quote)
{
	(*j)++;
	while (full_arg[*j] != quote)
	{
		if (full_arg[*j] != 'n')
			return (1);
		(*j)++;
	}
	(*j)++;
	return (0);
}

int	check_option_format(char *full_arg, char *option)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (full_arg[j] != option[i])
		j++;
	j++;
	while (full_arg[j] == 'n' || check_char(&full_arg[j]) < 0)
	{
		if (check_char(&full_arg[j]) < 0
			&& check_closing_quotes(&full_arg[j]) == 0)
		{
			if (check_option_format_in_quotes(full_arg, &j, full_arg[j]) == 1)
				return (1);
		}
		else if (full_arg[j] == 'n' || check_char(&full_arg[j]) < 0)
			j++;
	}
	if (!full_arg[j] || check_char(&full_arg[j]) == 1)
		return (0);
	else
		return (1);
}

char	*ft_strnstr_skip_quotes(char *big, char *little, size_t len)
{
	size_t	i;
	int		j;

	i = 0;
	if (little[i] == '\0')
		return (big);
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while (big[i] == little[j] && big && i < len)
		{
			++j;
			++i;
			if ((check_char(&big[i]) < 0 && check_char(&big[i + 1]) > 1
					&& big[i + 2] == big[i]) || (check_char(&big[i]) < 0
					&& check_char(&big[i - 1]) > 1 && big[i - 2] == big[i]))
				i++;
			if (little[j] == '\0')
				return (&big[i - j]);
		}
		i = i - j + 1;
	}
	return (NULL);
}
