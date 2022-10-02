/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_space_to_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:40:43 by blevrel           #+#    #+#             */
/*   Updated: 2022/09/28 11:39:30 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	add_space_to_parsing(char *cmd, char *arg, int i)
{
	static int	cmd_is_echo = 0;
	int			size;
	int			index;

	index = ft_strstr_index(arg, cmd);
	size = ft_strlen(cmd);
	if (i == 0)
	{
		if (ft_strcmp(cmd, "echo") == 0)
			cmd_is_echo = 1;
	}
	else if (cmd_is_echo == 1 && check_char(arg[index]) == 1
		&& check_char(arg[index - 1]) <= 0)
		cmd[size] = ' ';
	if (!arg[index])
		cmd_is_echo = 0;
}

char	*ft_strdup_add_space(const char *s)
{
	int		i;
	char	*res;

	i = 0;
	if (!s)
		return (NULL);
	res = ft_calloc((ft_strlen(s) + 2), sizeof(char));
	if (!res)
		return (NULL);
	while (s[i])
	{
		res[i] = (char)s[i];
		++i;
	}
	return (res);
}
