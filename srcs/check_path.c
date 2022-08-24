/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirabaud <pirabaud@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:10:54 by pirabaud          #+#    #+#             */
/*   Updated: 2022/08/24 16:35:31 by pirabaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*init_res(char *path, char *cmd)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(path, "/");
	res = ft_strjoin(tmp, cmd);
	free(tmp);
	return (res);
}

char	*check_path(char *cmd, char **env)
{
	int		i;
	char	*res;
	char	**path;

	i = 0;
	while (ft_memcmp(env[i], "PATH", 4) != 0)
		i++;
	path = ft_split(env[i], ':');
	i = 0;
	res = init_res(path[i++], cmd);
	while (access(res, F_OK) != 0 && path[i] != NULL)
	{
		free(res);
		res = init_res(path[i++], cmd);
	}
	free_double_tab(path);
	if (access(res, F_OK) == 0)
		return (res);
	free(res);
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	else
		return (NULL);
}
